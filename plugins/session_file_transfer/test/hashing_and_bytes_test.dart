import 'dart:typed_data';

import 'package:session_file_transfer/session_file_transfer.dart';
import 'package:test/test.dart';

void main() {
  test('streaming hash matches full-buffer hash', () async {
    final bytes = Uint8List.fromList(List<int>.generate(50 * 1024, (i) => i % 251));
    final fromStream = await Sha256Hasher.hashStream(Stream.value(bytes));
    final fromBytes = Sha256Hasher.hashBytes(bytes);
    expect(fromStream, fromBytes);
  });

  test('manifest fingerprint is stable', () {
    final a = Sha256Hasher.manifestFingerprint([
      (path: 'a.txt', size: 3, sha256: 'abc'),
      (path: 'b.bin', size: 9, sha256: 'def'),
    ]);
    final b = Sha256Hasher.manifestFingerprint([
      (path: 'a.txt', size: 3, sha256: 'abc'),
      (path: 'b.bin', size: 9, sha256: 'def'),
    ]);
    expect(a, b);
  });

  test('buildFromNamedBytes always hashes', () async {
    final sources = await FileManifestBuilder().buildFromNamedBytes([
      (relativePath: 'hello.txt', bytes: Uint8List.fromList('hi'.codeUnits)),
    ]);
    expect(sources.single.entry.sha256, isNotNull);
    expect(sources.single.entry.size, 2);
  });
}
