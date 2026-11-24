import 'dart:convert';
import 'dart:typed_data';

import 'package:session_terminal_link/session_terminal_link.dart';
import 'package:test/test.dart';

void main() {
  test('TermChunkCodec round-trip', () {
    final payload = utf8.encode('hello\n');
    final encoded = TermChunkCodec.encode(
      sessionId: 'abc123',
      payload: payload,
      isStderr: true,
    );
    expect(encoded[0], kTermChunkOpcode);
    final decoded = TermChunkCodec.tryDecode(encoded);
    expect(decoded, isNotNull);
    expect(decoded!.isStderr, isTrue);
    expect(decoded.sessionIdCrc32, TermChunkCodec.sessionIdCrc32('abc123'));
    expect(utf8.decode(decoded.payload), 'hello\n');
  });

  test('TermChunkCodec rejects wrong opcode', () {
    final buf = Uint8List.fromList([0, 1, 2, 3, 4, 5, 6]);
    expect(TermChunkCodec.tryDecode(buf), isNull);
  });

  test('TermLinkJsonCodec round-trip', () {
    final control = TermLinkControl(
      op: TermLinkOp.open,
      name: 'dev',
      shell: 'powershell.exe',
      cols: 80,
      rows: 24,
    );
    final text = TermLinkJsonCodec.encodeControl(control);
    final decoded = TermLinkJsonCodec.tryDecodeText(text);
    expect(decoded, isNotNull);
    expect(decoded!.op, TermLinkOp.open);
    expect(decoded.name, 'dev');
    expect(decoded.shell, 'powershell.exe');
    expect(decoded.cols, 80);
    expect(decoded.rows, 24);
  });

  test('isTermLinkEnvelope', () {
    expect(
      TermLinkJsonCodec.isTermLinkEnvelope({
        kTermLinkJsonKey: {'op': 'list'},
      }),
      isTrue,
    );
    expect(TermLinkJsonCodec.isTermLinkEnvelope({'clipboard': 'x'}), isFalse);
  });
}
