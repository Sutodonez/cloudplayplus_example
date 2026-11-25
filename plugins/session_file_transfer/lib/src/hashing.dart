import 'dart:typed_data';

import 'package:crypto/crypto.dart';

/// Streaming / chunked SHA-256 helpers (no dart:io).
abstract final class Sha256Hasher {
  /// Hash an entire byte stream.
  static Future<String> hashStream(Stream<List<int>> stream) async {
    final digest = await sha256.bind(stream).first;
    return digest.toString();
  }

  /// Hash [bytes] (full buffer).
  static String hashBytes(Uint8List bytes) => sha256.convert(bytes).toString();

  /// Hash the first [length] bytes of [bytes].
  static String hashPrefixBytes(Uint8List bytes, int length) {
    final n = length.clamp(0, bytes.length);
    return sha256.convert(Uint8List.sublistView(bytes, 0, n)).toString();
  }

  /// Content fingerprint for a manifest: sha256 over `"path:size:sha\\n"` lines.
  static String manifestFingerprint(
    Iterable<({String path, int size, String? sha256})> files,
  ) {
    final buf = StringBuffer();
    for (final f in files) {
      buf.writeln('${f.path}:${f.size}:${f.sha256 ?? ''}');
    }
    return sha256.convert(buf.toString().codeUnits).toString();
  }
}
