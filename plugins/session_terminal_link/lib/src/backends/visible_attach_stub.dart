/// Stub Windows Terminal visible-attach result for non-IO platforms (Web).
class WindowsTerminalVisibleAttach {
  final bool ok;
  final String detail;
  final int? pid;

  const WindowsTerminalVisibleAttach({
    required this.ok,
    required this.detail,
    this.pid,
  });

  static Future<String?> findWtExe() async => null;

  static Future<void> ensureProfile({
    required String profileName,
    required String commandLine,
  }) async {
    throw UnsupportedError('Windows Terminal attach requires dart:io');
  }

  static Future<WindowsTerminalVisibleAttach> attach({
    String? psmuxExe,
    String? psmuxAttachSession,
    String? commandLine,
    String? displayName,
  }) async {
    return const WindowsTerminalVisibleAttach(
      ok: false,
      detail: 'visible_attach requires dart:io Windows host',
    );
  }
}
