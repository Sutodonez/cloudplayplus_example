import 'dart:typed_data';

import 'protocol.dart';

/// One local file ready to send (path-backed or memory-backed).
///
/// Web controllers use [BytesFileSource]; desktop uses path-backed sources
/// from [FileManifestBuilder].
abstract class LocalFileSource {
  FileEntry get entry;

  /// Read up to [length] bytes starting at [offset].
  Future<Uint8List> readAt(int offset, int length);

  /// Stream the whole file (for hashing).
  Stream<List<int>> openRead();
}

/// In-memory source (Web file picker / tests).
class BytesFileSource implements LocalFileSource {
  BytesFileSource({
    required Uint8List bytes,
    required this.entry,
  }) : _bytes = bytes;

  final Uint8List _bytes;

  @override
  final FileEntry entry;

  @override
  Future<Uint8List> readAt(int offset, int length) async {
    if (offset >= _bytes.length) return Uint8List(0);
    final end = (offset + length).clamp(0, _bytes.length);
    return Uint8List.sublistView(_bytes, offset, end);
  }

  @override
  Stream<List<int>> openRead() async* {
    // Chunk to keep hashing incremental for large in-memory blobs.
    const step = 64 * 1024;
    for (var i = 0; i < _bytes.length; i += step) {
      final end = (i + step).clamp(0, _bytes.length);
      yield Uint8List.sublistView(_bytes, i, end);
    }
  }
}
