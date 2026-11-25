import 'dart:convert';
import 'dart:io';
import 'dart:typed_data';

import 'package:path/path.dart' as p;
import 'package:session_file_transfer/session_file_transfer.dart';
import 'package:test/test.dart';

String _fakeSha([int seed = 0]) =>
    List.generate(64, (i) => ((seed + i) % 16).toRadixString(16)).join();

void main() {
  group('validateIncomingOffer', () {
    test('requires sha256 on every file', () {
      final offer = FileXferControl(
        op: FileXferOp.offer,
        transferId: 't1',
        files: [
          FileEntry(relativePath: 'a.bin', size: 1, sha256: _fakeSha()),
          const FileEntry(relativePath: 'b.bin', size: 1),
        ],
      );
      expect(
        FileTransferEngine.validateIncomingOffer(offer),
        contains('sha256'),
      );
    });

    test('rejects invalid sha256 length', () {
      final offer = FileXferControl(
        op: FileXferOp.offer,
        transferId: 't1',
        files: [
          const FileEntry(relativePath: 'a.bin', size: 1, sha256: 'deadbeef'),
        ],
      );
      expect(
        FileTransferEngine.validateIncomingOffer(offer),
        contains('sha256'),
      );
    });

    test('rejects too many files', () {
      final files = List.generate(
        FileXferLimits.maxFilesPerOffer + 1,
        (i) => FileEntry(
          relativePath: 'f$i.bin',
          size: 1,
          sha256: _fakeSha(i),
        ),
      );
      final offer = FileXferControl(
        op: FileXferOp.offer,
        transferId: 't1',
        files: files,
      );
      expect(
        FileTransferEngine.validateIncomingOffer(offer),
        contains('too many files'),
      );
    });

    test('rejects oversized declared total', () {
      final offer = FileXferControl(
        op: FileXferOp.offer,
        transferId: 't1',
        files: [
          FileEntry(
            relativePath: 'huge.bin',
            size: FileXferLimits.maxTotalDeclaredBytes + 1,
            sha256: _fakeSha(),
          ),
        ],
      );
      expect(
        FileTransferEngine.validateIncomingOffer(offer),
        contains('declared total'),
      );
    });

    test('accepts well-formed offer', () {
      final offer = FileXferControl(
        op: FileXferOp.offer,
        transferId: 't1',
        files: [
          FileEntry(relativePath: 'a.bin', size: 10, sha256: _fakeSha(1)),
          FileEntry(relativePath: 'b.bin', size: 20, sha256: _fakeSha(2)),
        ],
      );
      expect(FileTransferEngine.validateIncomingOffer(offer), isNull);
    });
  });

  test('tryDecodeText rejects oversized control JSON', () {
    final pad = 'x' * (FileXferLimits.maxControlJsonBytes + 64);
    final text = jsonEncode({
      kFileXferJsonKey: {
        'op': FileXferOp.offer,
        'transferId': 't',
        'files': [],
        'pad': pad,
      },
    });
    expect(FileXferJsonCodec.tryDecodeText(text), isNull);
  });

  test('rejects new offer while transfer is active', () async {
    final tmp = await Directory.systemTemp.createTemp('cpp_offer_busy_');
    addTearDown(() async {
      if (await tmp.exists()) await tmp.delete(recursive: true);
    });

    late FileTransferEngine receiver;
    final rejected = <String>[];
    receiver = FileTransferEngine(
      sendText: (t) async {
        final c = FileXferJsonCodec.tryDecodeText(t);
        if (c?.op == FileXferOp.reject) {
          rejected.add(c!.error ?? '');
        }
      },
      sendBinary: (_) async {},
      receiveRoot: p.join(tmp.path, 'r'),
      autoAcceptIncoming: true,
    );

    final first = FileXferControl(
      op: FileXferOp.offer,
      transferId: 'first',
      files: [FileEntry(relativePath: 'a.bin', size: 4, sha256: _fakeSha(1))],
      bytesTotal: 4,
    );
    receiver.onTextMessage(FileXferJsonCodec.encodeControl(first));
    await Future<void>.delayed(const Duration(milliseconds: 30));
    expect(receiver.activeTransferId, 'first');

    final second = FileXferControl(
      op: FileXferOp.offer,
      transferId: 'second',
      files: [FileEntry(relativePath: 'b.bin', size: 4, sha256: _fakeSha(2))],
      bytesTotal: 4,
    );
    receiver.onTextMessage(FileXferJsonCodec.encodeControl(second));
    await Future<void>.delayed(const Duration(milliseconds: 30));

    expect(receiver.activeTransferId, 'first');
    expect(
      rejected.any((e) => e.contains('already in progress')),
      isTrue,
    );
    receiver.dispose();
  });

  test('chunk past declared size aborts transfer', () async {
    final tmp = await Directory.systemTemp.createTemp('cpp_offer_limits_');
    addTearDown(() async {
      if (await tmp.exists()) await tmp.delete(recursive: true);
    });

    late FileTransferEngine receiver;
    final rejected = <String>[];
    receiver = FileTransferEngine(
      sendText: (t) async {
        final c = FileXferJsonCodec.tryDecodeText(t);
        if (c?.op == FileXferOp.abort || c?.op == FileXferOp.reject) {
          rejected.add(c!.error ?? c.op);
        }
      },
      sendBinary: (_) async {},
      receiveRoot: p.join(tmp.path, 'r'),
      autoAcceptIncoming: true,
    );

    final sha = _fakeSha(9);
    final offer = FileXferControl(
      op: FileXferOp.offer,
      transferId: 'overflow',
      files: [FileEntry(relativePath: 'a.bin', size: 4, sha256: sha)],
      bytesTotal: 4,
    );
    receiver.onTextMessage(FileXferJsonCodec.encodeControl(offer));
    await Future<void>.delayed(const Duration(milliseconds: 30));

    final overrun = FileChunkCodec.encode(
      transferId: 'overflow',
      fileIndex: 0,
      offset: 0,
      payload: Uint8List.fromList([1, 2, 3, 4, 5]),
    );
    receiver.onBinaryMessage(overrun);
    await Future<void>.delayed(const Duration(milliseconds: 50));

    expect(rejected.any((e) => e.contains('exceeds declared size')), isTrue);
    receiver.dispose();
  });
}
