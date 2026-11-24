import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'dart:math';
import 'dart:typed_data';

import 'protocol.dart';

/// Default interactive shell for the current host OS.
///
/// Windows defaults to PowerShell (UU public docs); macOS/Linux use `$SHELL`
/// with bash/zsh fallbacks. This is a pipe-backed process, **not** ConPTY —
/// full TTY/mux is a documented gap (see plugin README / GV reference).
String defaultHostShell() {
  if (Platform.isWindows) {
    return 'powershell.exe';
  }
  final env = Platform.environment['SHELL'];
  if (env != null && env.isNotEmpty) return env;
  if (Platform.isMacOS) return '/bin/zsh';
  return '/bin/bash';
}

List<String> shellLaunchArgs(String shell) {
  final lower = shell.toLowerCase();
  if (Platform.isWindows) {
    if (lower.endsWith('powershell.exe') || lower.endsWith('pwsh.exe')) {
      return ['-NoLogo', '-NoExit'];
    }
    if (lower.endsWith('cmd.exe')) {
      return ['/K'];
    }
    return const [];
  }
  // Best-effort interactive login-less shell.
  return ['-i'];
}

/// Ring buffer of recent stdout/stderr for detach → reattach replay.
class _OutputRing {
  final int capacityBytes;
  final List<int> _bytes = [];

  _OutputRing({this.capacityBytes = 64 * 1024});

  void add(List<int> chunk) {
    _bytes.addAll(chunk);
    if (_bytes.length > capacityBytes) {
      _bytes.removeRange(0, _bytes.length - capacityBytes);
    }
  }

  Uint8List snapshot() => Uint8List.fromList(_bytes);
}

/// One host-side shell process owned by [TerminalLinkEngine] (host role).
class HostShellSession {
  final String sessionId;
  final String name;
  final String shell;
  int cols;
  int rows;

  Process? _process;
  StreamSubscription<List<int>>? _stdoutSub;
  StreamSubscription<List<int>>? _stderrSub;
  final _OutputRing _ring = _OutputRing();
  final _outputController = StreamController<TerminalOutputEvent>.broadcast();
  final _stateController = StreamController<TermSessionInfo>.broadcast();

  TermSessionState _state = TermSessionState.starting;
  int? _exitCode;
  String? _error;
  bool _attached = true;
  bool _disposed = false;

  HostShellSession({
    required this.sessionId,
    required this.name,
    required this.shell,
    this.cols = 120,
    this.rows = 40,
  });

  Stream<TerminalOutputEvent> get output => _outputController.stream;
  Stream<TermSessionInfo> get stateChanges => _stateController.stream;

  TermSessionInfo get info => TermSessionInfo(
        sessionId: sessionId,
        name: name,
        shell: shell,
        state: _attached
            ? (_state == TermSessionState.ready
                ? TermSessionState.attached
                : _state)
            : (_state == TermSessionState.ready ||
                    _state == TermSessionState.attached
                ? TermSessionState.detached
                : _state),
        cols: cols,
        rows: rows,
        exitCode: _exitCode,
        error: _error,
      );

  Future<void> start() async {
    if (_disposed) return;
    try {
      final args = shellLaunchArgs(shell);
      final process = await Process.start(
        shell,
        args,
        runInShell: false,
        workingDirectory: Platform.environment['USERPROFILE'] ??
            Platform.environment['HOME'],
        environment: _augmentedEnvironment(),
      );
      _process = process;
      _state = TermSessionState.ready;
      _emitState();

      _stdoutSub = process.stdout.listen((chunk) {
        _ring.add(chunk);
        if (_attached && !_outputController.isClosed) {
          _outputController.add(TerminalOutputEvent(
            sessionId: sessionId,
            bytes: chunk,
          ));
        }
      }, onError: (Object e) {
        _error = e.toString();
      });

      _stderrSub = process.stderr.listen((chunk) {
        _ring.add(chunk);
        if (_attached && !_outputController.isClosed) {
          _outputController.add(TerminalOutputEvent(
            sessionId: sessionId,
            bytes: chunk,
            isStderr: true,
          ));
        }
      });

      // ignore: unawaited_futures
      process.exitCode.then((code) {
        _exitCode = code;
        _state = TermSessionState.exited;
        _emitState();
      });
    } catch (e) {
      _error = e.toString();
      _state = TermSessionState.failed;
      _emitState();
      rethrow;
    }
  }

  Map<String, String> _augmentedEnvironment() {
    final env = Map<String, String>.from(Platform.environment);
    // Hint columns/rows for tools that read them (no real PTY yet).
    env['COLUMNS'] = cols.toString();
    env['LINES'] = rows.toString();
    env['TERM'] = env['TERM'] ?? 'xterm-256color';
    return env;
  }

  void attach() {
    _attached = true;
    final replay = _ring.snapshot();
    if (replay.isNotEmpty && !_outputController.isClosed) {
      _outputController.add(TerminalOutputEvent(
        sessionId: sessionId,
        bytes: replay,
      ));
    }
    if (_state == TermSessionState.ready ||
        _state == TermSessionState.detached) {
      _state = TermSessionState.ready;
    }
    _emitState();
  }

  void detach() {
    _attached = false;
    if (_state == TermSessionState.ready ||
        _state == TermSessionState.attached) {
      _state = TermSessionState.detached;
    }
    _emitState();
  }

  void resize(int newCols, int newRows) {
    cols = newCols;
    rows = newRows;
    // Without ConPTY/ioctl TIOCSWINSZ this is informational only.
    _emitState();
  }

  void writeInput(String data) {
    final proc = _process;
    if (proc == null || _state == TermSessionState.exited) return;
    proc.stdin.add(utf8.encode(data));
  }

  Future<void> kill() async {
    final proc = _process;
    if (proc != null) {
      proc.kill(ProcessSignal.sigkill);
      try {
        await proc.exitCode.timeout(const Duration(seconds: 2));
      } catch (_) {}
    }
    _state = TermSessionState.exited;
    _emitState();
  }

  void _emitState() {
    if (!_stateController.isClosed) {
      _stateController.add(info);
    }
  }

  Future<void> dispose() async {
    if (_disposed) return;
    _disposed = true;
    await _stdoutSub?.cancel();
    await _stderrSub?.cancel();
    await kill();
    await _outputController.close();
    await _stateController.close();
  }
}

/// Allocate a short opaque session id.
String newTerminalSessionId() {
  final r = Random.secure();
  final bytes = List<int>.generate(8, (_) => r.nextInt(256));
  return bytes.map((b) => b.toRadixString(16).padLeft(2, '0')).join();
}
