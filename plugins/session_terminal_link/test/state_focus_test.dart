import 'package:session_terminal_link/session_terminal_link.dart';
import 'package:test/test.dart';

void main() {
  test('state updates preserve mux metadata and do not steal focus', () async {
    late TerminalLinkEngine client;

    client = TerminalLinkEngine(
      isHost: false,
      sendText: (_) async {},
      sendBinary: (_) async {},
    );

    // Seed list_result with mux metadata (as after a successful list).
    client.onTextMessage(TermLinkJsonCodec.encodeControl(TermLinkControl(
      op: TermLinkOp.listResult,
      sessions: const [
        TermSessionInfo(
          sessionId: 'a',
          name: 'session-a',
          shell: 'powershell.exe',
          state: TermSessionState.ready,
          backend: 'psmux+conpty',
          muxSession: 'cppp-a',
          panes: ['%0'],
        ),
        TermSessionInfo(
          sessionId: 'b',
          name: 'session-b',
          shell: 'powershell.exe',
          state: TermSessionState.ready,
          backend: 'psmux+conpty',
          muxSession: 'cppp-b',
          panes: ['%0'],
        ),
      ],
    )));

    await client.attach('a');
    expect(client.activeSessionId, 'a');

    // Lifecycle state without mux fields must not wipe cached metadata.
    client.onTextMessage(TermLinkJsonCodec.encodeControl(const TermLinkControl(
      op: TermLinkOp.state,
      sessionId: 'a',
      name: 'session-a',
      shell: 'powershell.exe',
      cols: 100,
      rows: 30,
      state: TermSessionState.ready,
    )));

    final afterResize = client.knownSessions
        .firstWhere((s) => s.sessionId == 'a');
    expect(afterResize.backend, 'psmux+conpty');
    expect(afterResize.muxSession, 'cppp-a');
    expect(afterResize.panes, ['%0']);
    expect(afterResize.cols, 100);
    expect(client.activeSessionId, 'a');

    // Unrelated session ready must not steal activeSessionId.
    client.onTextMessage(TermLinkJsonCodec.encodeControl(const TermLinkControl(
      op: TermLinkOp.state,
      sessionId: 'b',
      name: 'session-b',
      shell: 'powershell.exe',
      state: TermSessionState.attached,
      backend: 'psmux+conpty',
      muxSession: 'cppp-b',
      panes: ['%0', '%1'],
    )));
    expect(client.activeSessionId, 'a');

    // Wire mux fields on state still flow through.
    final b = client.knownSessions.firstWhere((s) => s.sessionId == 'b');
    expect(b.panes, ['%0', '%1']);

    await client.dispose();
  });

}
