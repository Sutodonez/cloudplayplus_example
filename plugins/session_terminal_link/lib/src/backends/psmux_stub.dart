/// Stub [PsmuxCli] for platforms without `dart:io` (Web).
class PsmuxCli {
  final String executable;

  const PsmuxCli(this.executable);

  static Future<PsmuxCli?> detect() async => null;

  List<String> attachArgv(String sessionName) => const [];

  Future<void> newSession({
    required String name,
    String? shell,
    int cols = 120,
    int rows = 40,
  }) async {
    throw UnsupportedError('psmux requires dart:io');
  }

  Future<void> killSession(String name) async {
    throw UnsupportedError('psmux requires dart:io');
  }

  Future<bool> hasSession(String name) async => false;

  Future<void> splitWindow({
    required String target,
    bool vertical = true,
    String? shell,
  }) async {
    throw UnsupportedError('psmux requires dart:io');
  }

  Future<void> selectPane({
    required String target,
    required String pane,
  }) async {
    throw UnsupportedError('psmux requires dart:io');
  }

  Future<List<String>> listPanes(String target) async => const [];
}
