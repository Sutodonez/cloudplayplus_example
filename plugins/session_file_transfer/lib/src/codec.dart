import 'dart:convert';
import 'dart:typed_data';

import 'protocol.dart';

/// Binary chunk layout (little-endian):
/// ```
/// [0]     opcode = kFileChunkOpcode
/// [1..4]  transferIdCrc32
/// [5..6]  fileIndex (uint16)
/// [7..14] offset (uint64)
/// [15..]  payload
/// ```
abstract final class FileChunkCodec {
  static const int headerLength = 15;

  /// Stable 32-bit fingerprint of a transfer id string.
  static int transferIdCrc32(String transferId) {
    // CRC-32/ISO-HDLC over UTF-8 bytes.
    var crc = 0xffffffff;
    final bytes = utf8.encode(transferId);
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
    required String transferId,
    required int fileIndex,
    required int offset,
    required Uint8List payload,
  }) {
    final out = Uint8List(headerLength + payload.length);
    final view = ByteData.view(out.buffer, out.offsetInBytes, out.length);
    view.setUint8(0, kFileChunkOpcode);
    view.setUint32(1, transferIdCrc32(transferId), Endian.little);
    view.setUint16(5, fileIndex, Endian.little);
    _setUint64(view, 7, offset);
    out.setRange(headerLength, out.length, payload);
    return out;
  }

  static FileChunk? tryDecode(Uint8List buffer) {
    if (buffer.length < headerLength) return null;
    if (buffer[0] != kFileChunkOpcode) return null;
    final view = ByteData.view(buffer.buffer, buffer.offsetInBytes, buffer.length);
    final idCrc = view.getUint32(1, Endian.little);
    final fileIndex = view.getUint16(5, Endian.little);
    final offset = _getUint64(view, 7);
    final payload = Uint8List.sublistView(buffer, headerLength);
    return FileChunk(
      transferIdCrc32: idCrc,
      fileIndex: fileIndex,
      offset: offset,
      payload: payload,
    );
  }

  static void _setUint64(ByteData view, int byteOffset, int value) {
    // Split to avoid relying on ByteData.setUint64 on all platforms.
    view.setUint32(byteOffset, value & 0xffffffff, Endian.little);
    view.setUint32(byteOffset + 4, (value >> 32) & 0xffffffff, Endian.little);
  }

  static int _getUint64(ByteData view, int byteOffset) {
    final lo = view.getUint32(byteOffset, Endian.little);
    final hi = view.getUint32(byteOffset + 4, Endian.little);
    return (hi << 32) | lo;
  }
}

class FileChunk {
  final int transferIdCrc32;
  final int fileIndex;
  final int offset;
  final Uint8List payload;

  const FileChunk({
    required this.transferIdCrc32,
    required this.fileIndex,
    required this.offset,
    required this.payload,
  });
}

abstract final class FileXferJsonCodec {
  static String encodeControl(FileXferControl control) =>
      jsonEncode(control.toEnvelope());

  static FileXferControl? tryDecodeText(String text) {
    try {
      final decoded = jsonDecode(text);
      if (decoded is! Map) return null;
      final map = Map<String, dynamic>.from(decoded);
      if (!map.containsKey(kFileXferJsonKey)) return null;
      return FileXferControl.fromEnvelope(map);
    } catch (_) {
      return null;
    }
  }

  static bool isFileXferEnvelope(Map<String, dynamic> map) =>
      map.containsKey(kFileXferJsonKey);
}
