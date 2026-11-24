import 'dart:async';
import 'dart:io';
import 'dart:typed_data';

import 'package:path/path.dart' as p;
import 'package:session_file_transfer/session_file_transfer.dart';
import 'package:test/test.dart';

void main() {
  test('loopback file + folder transfer with resume ledger', () async {
    final tmp = await Directory.systemTemp.createTemp('cpp_xfer_');
    addTearDown(() async {
      if (await tmp.exists()) await tmp.delete(recursive: true);
    });

    final sendRoot = Directory(p.join(tmp.path, 'send'));
    final recvRoot = Directory(p.join(tmp.path, 'recv'));
    await sendRoot.create();
    await recvRoot.create();

    final fileA = File(p.join(sendRoot.path, 'hello.txt'));
    await fileA.writeAsString('hello-cloudplayplus');
    final nested = Directory(p.join(sendRoot.path, 'folder', 'nested'));
    await nested.create(recursive: true);
    final fileB = File(p.join(nested.path, 'data.bin'));
    await fileB.writeAsBytes(List<int>.generate(40 * 1024, (i) => i % 256));

    late FileTransferEngine alice;
    late FileTransferEngine bob;

    Future<void> pipeText(String text, void Function(String) into) async {
      into(text);
    }

    Future<void> pipeBinary(Uint8List bytes, void Function(Uint8List) into) async {
      into(bytes);
    }

    alice = FileTransferEngine(
      sendText: (t) => pipeText(t, (x) => bob.onTextMessage(x)),
      sendBinary: (b) => pipeBinary(b, (x) => bob.onBinaryMessage(x)),
      receiveRoot: p.join(tmp.path, 'alice_recv'),
      chunkSize: 4096,
      maxInFlight: 4,
      autoAcceptIncoming: true,
    );
    bob = FileTransferEngine(
      sendText: (t) => pipeText(t, (x) => alice.onTextMessage(x)),
      sendBinary: (b) => pipeBinary(b, (x) => alice.onBinaryMessage(x)),
      receiveRoot: recvRoot.path,
      chunkSize: 4096,
      maxInFlight: 4,
      autoAcceptIncoming: true,
    );

    final done = Completer<FileTransferProgress>();
    late final StreamSubscription sub;
    sub = bob.progress.listen((p) {
      if (p.state == FileTransferState.completed) {
        done.complete(p);
        sub.cancel();
      } else if (p.state == FileTransferState.failed) {
        done.completeError(p.error ?? 'failed');
        sub.cancel();
      }
    });

    await alice.sendPaths([fileA.path, p.join(sendRoot.path, 'folder')]);

    final result = await done.future.timeout(const Duration(seconds: 30));
    expect(result.fileCount, 2);

    final outA = File(p.join(recvRoot.path, 'hello.txt'));
    final outB = File(p.join(recvRoot.path, 'folder', 'nested', 'data.bin'));
    expect(await outA.readAsString(), 'hello-cloudplayplus');
    expect(await outB.readAsBytes(), await fileB.readAsBytes());

    alice.dispose();
    bob.dispose();
  });
}
