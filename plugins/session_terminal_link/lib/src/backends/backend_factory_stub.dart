import '../backends/psmux_stub.dart';
import 'shell_backend.dart';

/// Stub factory when `dart:io` is unavailable (Web cannot host shells).
class ShellBackendFactory {
  static Future<PsmuxCli?> psmux() async => null;

  static Future<ShellBackendChoice> create({
    required String shell,
    required List<String> shellArgs,
    required int cols,
    required int rows,
    String? muxSessionName,
    bool preferMux = true,
  }) async {
    throw UnsupportedError(
      'Shell backends require dart:io (Web cannot be terminal host)',
    );
  }
}
