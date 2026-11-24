import 'dart:convert';
import 'dart:typed_data';

import 'protocol.dart';

/// Binary chunk layout (little-endian):
/// ```
/// [0]     opcode = kTermChunkOpcode
/// [1..4]  sessionIdCrc32
/// [5]     flags (bit0 = stderr)
/// [6..]   payload
/// ```
abstract final class TermChunkCodec {
  static const int headerLength = 6;
  static const int flagStderr = 1 << 0;

  /// Stable 32-bit fingerprint of a session id string.
  static int sessionIdCrc32(String sessionId) {
    var crc = 0xffffffff;
    final bytes = utf8.encode(sessionId);
    for (final b in bytes) {
      crc ^= b;
      for (var i = 0; i < 8; i++) {
        final mask = -(crc & 1);
        crc = (crc >> 1) ^ (0xedb88320 & mask);
      }
    }
    return (~crc) & 0xffffffff;
  }

  static Uint8List encode({
    required String sessionId,
    required List<int> payload,
    bool isStderr = false,
  }) {
    final out = Uint8List(headerLength + payload.length);
    final view = ByteData.view(out.buffer, out.offsetInBytes, out.length);
    view.setUint8(0, kTermChunkOpcode);
    view.setUint32(1, sessionIdCrc32(sessionId), Endian.little);
    view.setUint8(5, isStderr ? flagStderr : 0);
    out.setRange(headerLength, out.length, payload);
    return out;
  }

  static TermChunk? tryDecode(Uint8List buffer) {
    if (buffer.length < headerLength) return null;
    if (buffer[0] != kTermChunkOpcode) return null;
    final view =
        ByteData.view(buffer.buffer, buffer.offsetInBytes, buffer.length);
    final idCrc = view.getUint32(1, Endian.little);
    final flags = view.getUint8(5);
    final payload = Uint8List.sublistView(buffer, headerLength);
    return TermChunk(
      sessionIdCrc32: idCrc,
      isStderr: (flags & flagStderr) != 0,
      payload: payload,
    );
  }
}

class TermChunk {
  final int sessionIdCrc32;
  final bool isStderr;
  final Uint8List payload;

  const TermChunk({
    required this.sessionIdCrc32,
    required this.isStderr,
    required this.payload,
  });
}

abstract final class TermLinkJsonCodec {
  static String encodeControl(TermLinkControl control) =>
      jsonEncode(control.toEnvelope());

  static TermLinkControl? tryDecodeText(String text) {
    try {
      final decoded = jsonDecode(text);
      if (decoded is! Map) return null;
      final map = Map<String, dynamic>.from(decoded);
      if (!map.containsKey(kTermLinkJsonKey)) return null;
      return TermLinkControl.fromEnvelope(map);
    } catch (_) {
      return null;
    }
  }

  static bool isTermLinkEnvelope(Map<String, dynamic> data) =>
      data.containsKey(kTermLinkJsonKey);
}
