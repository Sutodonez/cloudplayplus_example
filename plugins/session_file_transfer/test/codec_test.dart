import 'dart:convert';
import 'dart:typed_data';

import 'package:session_file_transfer/session_file_transfer.dart';
import 'package:test/test.dart';

void main() {
  group('FileChunkCodec', () {
    test('round-trips chunk header and payload', () {
      final payload = Uint8List.fromList(List<int>.generate(100, (i) => i));
      final encoded = FileChunkCodec.encode(
        transferId: 'xfer_test_1',
        fileIndex: 3,
        offset: 1 << 40, // exercises high 32 bits
        payload: payload,
      );
      expect(encoded[0], kFileChunkOpcode);
      final decoded = FileChunkCodec.tryDecode(encoded);
      expect(decoded, isNotNull);
      expect(decoded!.transferIdCrc32,
          FileChunkCodec.transferIdCrc32('xfer_test_1'));
      expect(decoded.fileIndex, 3);
      expect(decoded.offset, 1 << 40);
      expect(decoded.payload, payload);
    });

    test('rejects non-chunk opcodes', () {
      final buf = Uint8List.fromList([0, 1, 2, 3]);
      expect(FileChunkCodec.tryDecode(buf), isNull);
    });
  });

  group('FileXferJsonCodec', () {
    test('round-trips offer envelope', () {
      final control = FileXferControl(
        op: FileXferOp.offer,
        transferId: 'xfer_abc',
        files: const [
          FileEntry(relativePath: 'a/b.txt', size: 12, sha256: 'deadbeef'),
        ],
        bytesTotal: 12,
      );
      final text = FileXferJsonCodec.encodeControl(control);
      final map = jsonDecode(text) as Map<String, dynamic>;
      expect(map.containsKey(kFileXferJsonKey), isTrue);
      final parsed = FileXferJsonCodec.tryDecodeText(text);
      expect(parsed, isNotNull);
      expect(parsed!.op, FileXferOp.offer);
      expect(parsed.transferId, 'xfer_abc');
      expect(parsed.files.single.relativePath, 'a/b.txt');
      expect(parsed.files.single.size, 12);
      expect(parsed.files.single.sha256, 'deadbeef');
    });

    test('ignores unrelated json', () {
      expect(FileXferJsonCodec.tryDecodeText('{"clipboard":"x"}'), isNull);
    });
  });

  group('FileReceiveWriter.sanitizeRelative', () {
    test('blocks path escape', () {
      expect(
        () => FileReceiveWriter.sanitizeRelative('../etc/passwd'),
        throwsArgumentError,
      );
      expect(
        () => FileReceiveWriter.sanitizeRelative('/abs'),
        throwsArgumentError,
      );
      expect(FileReceiveWriter.sanitizeRelative(r'folder\file.txt'),
          'folder/file.txt');
    });
  });
}
