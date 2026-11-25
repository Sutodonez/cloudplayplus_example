import 'dart:async';
import 'dart:typed_data';

/// Host-side shell / PTY backend used by [HostShellSession].
abstract class ShellBackend {
  /// Human-readable backend id: `pipe`, `conpty`, `psmux+conpty`.
  String get kind;

  Stream<Uint8List> get stdout;

  Future<void> start({
    required String shell,
    required List<String> args,
    required int cols,
    required int rows,
    String? workingDirectory,
    Map<String, String>? environment,
  });

  void write(List<int> data);

  void resize(int cols, int rows);

  Future<void> kill();

  Future<int> get exitCode;

  Future<void> dispose();
}

/// Factory result when selecting a host backend.
class ShellBackendChoice {
  final ShellBackend backend;
  final String kind;
  final String detail;

  const ShellBackendChoice({
    required this.backend,
    required this.kind,
    required this.detail,
  });
}
