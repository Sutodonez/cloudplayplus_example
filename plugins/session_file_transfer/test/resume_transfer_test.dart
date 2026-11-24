import 'dart:async';
import 'dart:io';

import 'package:path/path.dart' as p;
import 'package:session_file_transfer/session_file_transfer.dart';
import 'package:test/test.dart';

void main() {
  test('re-offer resumes from partial on-disk bytes', () async {
    final tmp = await Directory.systemTemp.createTemp('cpp_resume_');
    addTearDown(() async {
      if (await tmp.exists()) await tmp.delete(recursive: true);
    });

    final payload = List<int>.generate(20 * 1024, (i) => i % 256);
    final src = File(p.join(tmp.path, 'big.bin'));
    await src.writeAsBytes(payload);

    final recvRoot = p.join(tmp.path, 'recv');
    await Directory(recvRoot).create();

    // Seed a partial file + ledger as if a prior transfer stopped mid-way.
    final partial = File(p.join(recvRoot, 'big.bin'));
    const already = 7000;
    await partial.writeAsBytes(payload.sublist(0, already));
    final store = ResumeStore(recvRoot);
    await store.saveProgress(
      transferId: 'xfer_old',
      files: [FileEntry(relativePath: 'big.bin', size: payload.length)],
      fileIndex: 0,
      resumeOffset: already,
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
}
