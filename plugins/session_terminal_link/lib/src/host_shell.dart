import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'dart:math';
import 'dart:typed_data';

import 'backends/backend_factory.dart';
import 'backends/psmux.dart';
import 'backends/shell_backend.dart';
import 'backends/visible_attach_win.dart';
import 'protocol.dart';

/// Default interactive shell for the current host OS.
///
/// Windows defaults to PowerShell (UU public docs); macOS/Linux use `$SHELL`
/// with bash/zsh fallbacks.
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

/// One host-side shell / PTY session owned by [TerminalLinkEngine] (host role).
class HostShellSession {
  final String sessionId;
  final String name;
  final String shell;
  int cols;
  int rows;

  ShellBackend? _backend;
  String _backendKind = 'pipe';
  String? _muxSession;
  List<String> _panes = const [];
  StreamSubscription<Uint8List>? _outSub;
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

  String get backendKind => _backendKind;
  String? get muxSession => _muxSession;

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
        backend: _backendKind,
        muxSession: _muxSession,
        panes: _panes,
      );

  Future<void> start() async {
    if (_disposed) return;
    try {
      final args = shellLaunchArgs(shell);
      // Use sessionId as mux name (hex, tmux-safe).
      final muxName = 'cppp-$sessionId';
      final choice = await ShellBackendFactory.create(
        shell: shell,
        shellArgs: args,
        cols: cols,
        rows: rows,
        muxSessionName: muxName,
        preferMux: Platform.isWindows,
      );
      _backend = choice.backend;
      _backendKind = choice.kind;
      if (choice.kind.startsWith('psmux')) {
        _muxSession = muxName;
        await _refreshPanes();
      }

      _state = TermSessionState.ready;
      _emitState();

      _outSub = choice.backend.stdout.listen((chunk) {
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

      // ignore: unawaited_futures
      choice.backend.exitCode.then((code) {
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

  Future<void> _refreshPanes() async {
    final mux = _muxSession;
    if (mux == null) return;
    final cli = await ShellBackendFactory.psmux();
    if (cli == null) return;
    _panes = await cli.listPanes(mux);
  }

  /// Split the psmux window into another pane (no-op without psmux).
  Future<void> splitPane({bool vertical = true}) async {
    final mux = _muxSession;
    final cli = await ShellBackendFactory.psmux();
    if (mux == null || cli == null) {
      throw StateError('split_pane requires a psmux-backed session on Windows');
    }
    await cli.splitWindow(target: mux, vertical: vertical, shell: shell);
    await _refreshPanes();
    _emitState();
  }

  Future<void> selectPane(String paneId) async {
    final mux = _muxSession;
    final cli = await ShellBackendFactory.psmux();
    if (mux == null || cli == null) {
      throw StateError('select_pane requires a psmux-backed session on Windows');
    }
    await cli.selectPane(target: mux, pane: paneId);
    _emitState();
  }

  /// Open a locally-visible Windows Terminal window on the host.
  Future<WindowsTerminalVisibleAttach> visibleAttach() async {
    final mux = _muxSession;
    final cli = await ShellBackendFactory.psmux();
    if (mux != null && cli != null) {
      await WindowsTerminalVisibleAttach.ensureProfile(
        profileName: 'CloudPlayPlus:$mux',
        commandLine: '${cli.executable} attach -t $mux',
      );
      return WindowsTerminalVisibleAttach.attach(
        psmuxExe: cli.executable,
        psmuxAttachSession: mux,
        displayName: name,
      );
    }
    // Without psmux: launch WT with the same shell (separate process — not a
    // shared PTY attach; documented limitation when mux is absent).
    return WindowsTerminalVisibleAttach.attach(
      commandLine: shell,
      displayName: name,
    );
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
    _backend?.resize(newCols, newRows);
    _emitState();
  }

  void writeInput(String data) {
    if (_backend == null || _state == TermSessionState.exited) return;
    _backend!.write(utf8.encode(data));
  }

  Future<void> kill() async {
    final mux = _muxSession;
    if (mux != null) {
      final cli = await ShellBackendFactory.psmux();
      try {
        await cli?.killSession(mux);
      } catch (_) {}
    }
    await _backend?.kill();
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
    await _outSub?.cancel();
    await kill();
    await _backend?.dispose();
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

/// Whether psmux was detected on this host (Windows only).
Future<bool> hostHasPsmux() async =>
    (await ShellBackendFactory.psmux()) != null;
