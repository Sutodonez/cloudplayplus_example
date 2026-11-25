import 'dart:async';
import 'dart:math';

import 'backends/visible_attach_stub.dart';
import 'protocol.dart';

/// Default interactive shell — not available without `dart:io`.
String defaultHostShell() =>
    throw UnsupportedError('Host shell requires dart:io (not available on Web)');

List<String> shellLaunchArgs(String shell) => const [];

/// Host-side shell session stub for platforms without `dart:io` (e.g. Web).
///
/// Web may be a **controller** only; hosting a shell is unsupported.
class HostShellSession {
  final String sessionId;
  final String name;
  final String shell;
  int cols;
  int rows;

  HostShellSession({
    required this.sessionId,
    required this.name,
    required this.shell,
    this.cols = 120,
    this.rows = 40,
  });

  Stream<TerminalOutputEvent> get output => const Stream.empty();
  Stream<TermSessionInfo> get stateChanges => const Stream.empty();

  String get backendKind => 'unsupported';
  String? get muxSession => null;

  TermSessionInfo get info => TermSessionInfo(
        sessionId: sessionId,
        name: name,
        shell: shell,
        state: TermSessionState.failed,
        cols: cols,
        rows: rows,
        error: 'Host shell requires dart:io (Web cannot be terminal host)',
        backend: backendKind,
      );

  Future<void> start() async {
    throw UnsupportedError(
      'Web cannot host terminal sessions (no dart:io / ConPTY)',
    );
  }

  Future<void> splitPane({bool vertical = true}) async {
    throw UnsupportedError('split_pane requires a dart:io host');
  }

  Future<void> selectPane(String paneId) async {
    throw UnsupportedError('select_pane requires a dart:io host');
  }

  Future<WindowsTerminalVisibleAttach> visibleAttach() async {
    throw UnsupportedError('visible_attach requires a dart:io Windows host');
  }

  void attach() {}

  void detach() {}

  void resize(int newCols, int newRows) {
    cols = newCols;
    rows = newRows;
  }

  void writeInput(String data) {}

  Future<void> kill() async {}

  Future<void> dispose() async {}
}

/// Allocate a short opaque session id.
String newTerminalSessionId() {
  final r = Random.secure();
  final bytes = List<int>.generate(8, (_) => r.nextInt(256));
  return bytes.map((b) => b.toRadixString(16).padLeft(2, '0')).join();
}

/// Whether psmux was detected on this host (always false without dart:io).
Future<bool> hostHasPsmux() async => false;
