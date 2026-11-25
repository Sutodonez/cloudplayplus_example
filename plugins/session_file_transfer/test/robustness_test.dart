import 'dart:async';
import 'dart:io';
import 'dart:typed_data';

import 'package:path/path.dart' as p;
import 'package:session_file_transfer/session_file_transfer.dart';
import 'package:test/test.dart';

void main() {
  test('send fails fast when channel send throws (no window hang)', () async {
    final tmp = await Directory.systemTemp.createTemp('cpp_xfer_robust_');
    addTearDown(() async {
      if (await tmp.exists()) await tmp.delete(recursive: true);
    });

    final events = <String>[];
    late FileTransferEngine sender;
    late FileTransferEngine receiver;

    sender = FileTransferEngine(
      sendText: (t) async {
        events.add('s-text');
        receiver.onTextMessage(t);
      },
      sendBinary: (b) async {
        events.add('s-bin');
        throw StateError('File transfer data channel is not open');
      },
      receiveRoot: p.join(tmp.path, 's'),
      chunkSize: 1024,
      maxInFlight: 2,
      autoAcceptIncoming: true,
    );
    receiver = FileTransferEngine(
      sendText: (t) async {
        events.add('r-text');
        sender.onTextMessage(t);
      },
      sendBinary: (b) async {
        events.add('r-bin');
        sender.onBinaryMessage(b);
      },
      receiveRoot: p.join(tmp.path, 'r'),
      chunkSize: 1024,
      maxInFlight: 2,
      autoAcceptIncoming: true,
    );

    final failed = Completer<FileTransferProgress>();
    final sub = sender.progress.listen((p) {
      if (p.state == FileTransferState.failed ||
          p.state == FileTransferState.aborted) {
        if (!failed.isCompleted) failed.complete(p);
      }
    });

    await sender.sendNamedBytes([
      (
        relativePath: 'a.bin',
        bytes: Uint8List.fromList(List<int>.generate(4096, (i) => i)),
      ),
    ]);

    final result = await failed.future.timeout(const Duration(seconds: 5));
    expect(result.error, contains('not open'));
    // Must have attempted binary send, but must not keep spinning forever.
    expect(events.where((e) => e == 's-bin'), isNotEmpty);

    await sub.cancel();
    await Future<void>.delayed(const Duration(milliseconds: 20));
    sender.dispose();
    receiver.dispose();
  });

  test('dispose notifies peer with abort', () async {
    final tmp = await Directory.systemTemp.createTemp('cpp_xfer_dispose_');
    addTearDown(() async {
      if (await tmp.exists()) await tmp.delete(recursive: true);
    });

    final peerControls = <FileXferControl>[];
    final holdChunks = Completer<void>();
    late FileTransferEngine alice;
    late FileTransferEngine bob;

    alice = FileTransferEngine(
      sendText: (t) async {
        final c = FileXferJsonCodec.tryDecodeText(t);
        if (c != null) peerControls.add(c);
        bob.onTextMessage(t);
      },
      sendBinary: (b) async {
        // Stall the send loop so dispose runs while transfer is active.
        await holdChunks.future;
        bob.onBinaryMessage(b);
      },
      receiveRoot: p.join(tmp.path, 'a'),
      chunkSize: 1024,
      maxInFlight: 4,
      autoAcceptIncoming: true,
    );
    bob = FileTransferEngine(
      sendText: (t) async => alice.onTextMessage(t),
      sendBinary: (b) async => alice.onBinaryMessage(b),
      receiveRoot: p.join(tmp.path, 'b'),
      chunkSize: 1024,
      maxInFlight: 4,
      autoAcceptIncoming: true,
    );

    final bobAborted = Completer<void>();
    final sub = bob.progress.listen((p) {
      if (p.state == FileTransferState.aborted && !bobAborted.isCompleted) {
        bobAborted.complete();
      }
    });

    await alice.sendNamedBytes([
      (
        relativePath: 'big.bin',
        bytes: Uint8List.fromList(List<int>.generate(64 * 1024, (i) => i)),
      ),
    ]);

    // Wait until accept puts sender into transferring, then dispose.
    await Future<void>.delayed(const Duration(milliseconds: 50));
    expect(alice.state, FileTransferState.transferring);
    alice.dispose();

    await bobAborted.future.timeout(const Duration(seconds: 5));
    expect(
      peerControls.any((c) => c.op == FileXferOp.abort),
      isTrue,
    );

    holdChunks.complete();
    await Future<void>.delayed(const Duration(milliseconds: 20));
    await sub.cancel();
    bob.dispose();
  });

  test('control messages are handled serially', () async {
    final order = <String>[];
    final gate = Completer<void>();

    late FileTransferEngine engine;
    engine = FileTransferEngine(
      sendText: (t) async {},
      sendBinary: (b) async {},
      receiveRoot: '/tmp/cpp_xfer_serial',
      autoAcceptIncoming: false,
    );
    engine.onIncomingOffer = (offer) async {
      order.add('offer-start');
      await gate.future;
      order.add('offer-end');
      return false;
    };

    final offer = FileXferJsonCodec.encodeControl(FileXferControl(
      op: FileXferOp.offer,
      transferId: 'xfer_serial_1',
      files: [
        FileEntry(relativePath: 'a.txt', size: 1),
      ],
      bytesTotal: 1,
    ));
    final rejectOther = FileXferJsonCodec.encodeControl(FileXferControl(
      op: FileXferOp.abort,
      transferId: 'xfer_other',
      error: 'unrelated',
    ));

    engine.onTextMessage(offer);
    // While offer handler is gated, enqueue another control; it must wait.
    engine.onTextMessage(rejectOther);
    await Future<void>.delayed(const Duration(milliseconds: 30));
    expect(order, ['offer-start']);

    gate.complete();
    await Future<void>.delayed(const Duration(milliseconds: 30));
    expect(order, ['offer-start', 'offer-end']);

    engine.dispose();
  });
}
