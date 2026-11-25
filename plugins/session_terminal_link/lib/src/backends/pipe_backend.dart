import 'dart:async';
import 'dart:io';
import 'dart:typed_data';

import 'shell_backend.dart';

/// Pipe-backed [Process] shell (no real PTY). Used on non-Windows hosts and
/// as a fallback when ConPTY / psmux are unavailable.
class PipeShellBackend implements ShellBackend {
  Process? _process;
  StreamController<Uint8List>? _stdout;
  StreamSubscription<List<int>>? _outSub;
  StreamSubscription<List<int>>? _errSub;
  Completer<int>? _exit;

  @override
  String get kind => 'pipe';

  @override
  Stream<Uint8List> get stdout {
    final c = _stdout;
    if (c == null) {
      throw StateError('PipeShellBackend not started');
    }
    return c.stream;
  }

  @override
  Future<void> start({
    required String shell,
    required List<String> args,
    required int cols,
    required int rows,
    String? workingDirectory,
    Map<String, String>? environment,
  }) async {
    _stdout = StreamController<Uint8List>.broadcast();
    _exit = Completer<int>();
    final env = Map<String, String>.from(environment ?? Platform.environment);
    env['COLUMNS'] = cols.toString();
    env['LINES'] = rows.toString();
    env['TERM'] = env['TERM'] ?? 'xterm-256color';

    final process = await Process.start(
      shell,
      args,
      runInShell: false,
      workingDirectory: workingDirectory,
      environment: env,
    );
    _process = process;

    _outSub = process.stdout.listen((chunk) {
      if (!(_stdout?.isClosed ?? true)) {
        _stdout!.add(Uint8List.fromList(chunk));
      }
    });
    _errSub = process.stderr.listen((chunk) {
      if (!(_stdout?.isClosed ?? true)) {
        _stdout!.add(Uint8List.fromList(chunk));
      }
    });

    // ignore: unawaited_futures
    process.exitCode.then((code) {
      if (!(_exit?.isCompleted ?? true)) _exit!.complete(code);
    });
  }

  @override
  void write(List<int> data) {
    _process?.stdin.add(data);
  }

  @override
  void resize(int cols, int rows) {
    // Informational only without a PTY.
  }

  @override
  Future<void> kill() async {
    final proc = _process;
    if (proc != null) {
      proc.kill(ProcessSignal.sigkill);
      try {
        await proc.exitCode.timeout(const Duration(seconds: 2));
      } catch (_) {}
    }
    if (!(_exit?.isCompleted ?? true)) _exit!.complete(-1);
  }

  @override
  Future<int> get exitCode => _exit?.future ?? Future.value(-1);

  @override
  Future<void> dispose() async {
    await _outSub?.cancel();
    await _errSub?.cancel();
    await kill();
    await _stdout?.close();
    _stdout = null;
  }
}
