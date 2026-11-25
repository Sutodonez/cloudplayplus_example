import 'package:session_terminal_link/session_terminal_link.dart';
import 'package:test/test.dart';

void main() {
  test('split_pane / visible_attach control round-trip', () {
    final split = TermLinkControl(
      op: TermLinkOp.splitPane,
      sessionId: 'abc',
      vertical: false,
    );
    final decoded = TermLinkJsonCodec.tryDecodeText(
      TermLinkJsonCodec.encodeControl(split),
    );
    expect(decoded!.op, TermLinkOp.splitPane);
    expect(decoded.vertical, isFalse);
    expect(decoded.sessionId, 'abc');

    final vis = TermLinkControl(
      op: TermLinkOp.visibleAttachResult,
      sessionId: 'abc',
      ok: true,
      detail: 'launched Windows Terminal pid=1',
    );
    final visDecoded = TermLinkJsonCodec.tryDecodeText(
      TermLinkJsonCodec.encodeControl(vis),
    );
    expect(visDecoded!.ok, isTrue);
    expect(visDecoded.detail, contains('Windows Terminal'));
  });

  test('TermSessionInfo carries backend and panes', () {
    final info = TermSessionInfo(
      sessionId: 's1',
      name: 'n',
      shell: 'powershell.exe',
      state: TermSessionState.attached,
      backend: 'psmux+conpty',
      muxSession: 'cppp-s1',
      panes: const ['%0', '%1'],
    );
    final again = TermSessionInfo.fromJson(info.toJson());
    expect(again.backend, 'psmux+conpty');
    expect(again.muxSession, 'cppp-s1');
    expect(again.panes, ['%0', '%1']);
  });

  test('state control round-trip preserves mux metadata', () {
    final control = TermLinkControl(
      op: TermLinkOp.state,
      sessionId: 's1',
      name: 'n',
      shell: 'powershell.exe',
      state: TermSessionState.ready,
      backend: 'psmux+conpty',
      muxSession: 'cppp-s1',
      panes: const ['%0', '%1'],
    );
    final decoded = TermLinkJsonCodec.tryDecodeText(
      TermLinkJsonCodec.encodeControl(control),
    );
    expect(decoded!.backend, 'psmux+conpty');
    expect(decoded.muxSession, 'cppp-s1');
    expect(decoded.panes, ['%0', '%1']);
  });
}
