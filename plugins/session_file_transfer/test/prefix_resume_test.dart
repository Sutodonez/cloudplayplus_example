import 'dart:async';
import 'dart:io';
import 'dart:typed_data';

import 'package:path/path.dart' as p;
import 'package:session_file_transfer/session_file_transfer.dart';
import 'package:test/test.dart';

void main() {
  test('prefix mismatch triggers resume_restart then full rewrite', () async {
    final tmp = await Directory.systemTemp.createTemp('cpp_prefix_');
    addTearDown(() async {
      if (await tmp.exists()) await tmp.delete(recursive: true);
    });

    final payload = Uint8List.fromList(List<int>.generate(12 * 1024, (i) => i % 256));
    final src = File(p.join(tmp.path, 'blob.bin'));
    await src.writeAsBytes(payload);

    final recvRoot = p.join(tmp.path, 'recv');
    await Directory(recvRoot).create();

    // Corrupt partial + ledger claiming 4096 good bytes.
    final partial = File(p.join(recvRoot, 'blob.bin'));
    await partial.writeAsBytes(List<int>.filled(4096, 7));
    final store = ResumeStore(recvRoot);
    await store.saveProgress(
      transferId: 'xfer_corrupt',
      files: [
        FileEntry(
          relativePath: 'blob.bin',
          size: payload.length,
          sha256: Sha256Hasher.hashBytes(payload),
        ),
      ],
      fileIndex: 0,
      resumeOffset: 4096,
      prefixSha256: 'deadbeef', // intentionally wrong vs disk
    );

    late FileTransferEngine alice;
    late FileTransferEngine bob;
    alice = FileTransferEngine(
      sendText: (t) async => bob.onTextMessage(t),
      sendBinary: (b) async => bob.onBinaryMessage(b),
      receiveRoot: p.join(tmp.path, 'alice_recv'),
      chunkSize: 2048,
      maxInFlight: 2,
    );
    bob = FileTransferEngine(
      sendText: (t) async => alice.onTextMessage(t),
      sendBinary: (b) async => alice.onBinaryMessage(b),
      receiveRoot: recvRoot,
      chunkSize: 2048,
      maxInFlight: 2,
      autoAcceptIncoming: true,
    );

    final done = Completer<void>();
    late final StreamSubscription sub;
    sub = bob.progress.listen((p) {
      if (p.state == FileTransferState.completed) {
        done.complete();
        sub.cancel();
      } else if (p.state == FileTransferState.failed) {
        done.completeError(p.error ?? 'failed');
        sub.cancel();
      }
    });

    await alice.sendPaths([src.path]);
    await done.future.timeout(const Duration(seconds: 30));

    expect(await partial.readAsBytes(), payload);
    alice.dispose();
    bob.dispose();
  });

  test('memory-backed send (web controller path) completes', () async {
    final tmp = await Directory.systemTemp.createTemp('cpp_mem_');
    addTearDown(() async {
      if (await tmp.exists()) await tmp.delete(recursive: true);
    });

    late FileTransferEngine alice;
    late FileTransferEngine bob;
    alice = FileTransferEngine(
      sendText: (t) async => bob.onTextMessage(t),
      sendBinary: (b) async => bob.onBinaryMessage(b),
      receiveRoot: p.join(tmp.path, 'alice'),
      chunkSize: 1024,
    );
    bob = FileTransferEngine(
      sendText: (t) async => alice.onTextMessage(t),
      sendBinary: (b) async => alice.onBinaryMessage(b),
      receiveRoot: p.join(tmp.path, 'bob'),
      chunkSize: 1024,
      autoAcceptIncoming: true,
    );

    final done = Completer<void>();
    bob.progress.listen((p) {
      if (p.state == FileTransferState.completed) done.complete();
      if (p.state == FileTransferState.failed) {
        done.completeError(p.error ?? 'failed');
      }
    });

    await alice.sendNamedBytes([
      (
        relativePath: 'from_web.txt',
        bytes: Uint8List.fromList('web-controller'.codeUnits),
      ),
    ]);
    await done.future.timeout(const Duration(seconds: 15));
    final out = File(p.join(tmp.path, 'bob', 'from_web.txt'));
    expect(await out.readAsString(), 'web-controller');
    alice.dispose();
    bob.dispose();
  });

  test('autoAcceptIncoming=false rejects without callback', () async {
    final tmp = await Directory.systemTemp.createTemp('cpp_reject_');
    addTearDown(() async {
      if (await tmp.exists()) await tmp.delete(recursive: true);
    });

    late FileTransferEngine alice;
    late FileTransferEngine bob;
    alice = FileTransferEngine(
      sendText: (t) async => bob.onTextMessage(t),
      sendBinary: (b) async => bob.onBinaryMessage(b),
      receiveRoot: p.join(tmp.path, 'a'),
    );
    bob = FileTransferEngine(
      sendText: (t) async => alice.onTextMessage(t),
      sendBinary: (b) async => alice.onBinaryMessage(b),
      receiveRoot: p.join(tmp.path, 'b'),
      autoAcceptIncoming: false,
    );

    final rejected = Completer<void>();
    alice.progress.listen((p) {
      if (p.state == FileTransferState.aborted) rejected.complete();
    });

    await alice.sendNamedBytes([
      (relativePath: 'x.txt', bytes: Uint8List.fromList([1, 2, 3])),
    ]);
    await rejected.future.timeout(const Duration(seconds: 5));
    alice.dispose();
    bob.dispose();
  });
}
