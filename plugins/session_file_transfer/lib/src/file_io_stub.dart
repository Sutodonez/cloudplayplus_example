import 'dart:typed_data';

import 'hashing.dart';
import 'local_source.dart';
import 'protocol.dart';

/// Web / non-IO stub: no filesystem receive root.
String defaultReceiveRoot() => 'web-unsupported-receive-root';

/// Builds sources from in-memory named blobs (Web file picker).
Future<List<LocalFileSource>> buildManifestFromNamedBytes(
  List<({String relativePath, Uint8List bytes})> files, {
  bool hashContent = true,
}) async {
  if (files.isEmpty) throw StateError('No files selected');
  final out = <LocalFileSource>[];
  for (final f in files) {
    final path = f.relativePath.replaceAll('\\', '/');
    final hash =
        hashContent ? await Sha256Hasher.hashStream(Stream.value(f.bytes)) : null;
    out.add(BytesFileSource(
      bytes: f.bytes,
      entry: FileEntry(relativePath: path, size: f.bytes.length, sha256: hash),
    ));
  }
  return out;
}

/// Path-based manifest is unavailable without dart:io.
Future<List<LocalFileSource>> buildManifestFromPaths(
  List<String> paths, {
  bool hashContent = true,
}) async {
  throw UnsupportedError(
      'Path-based file selection requires dart:io (not available on Web)');
}

class FileReceiveWriter {
  FileReceiveWriter(this.rootDir);

  final String rootDir;
  String? openRelPath;
  int expectedOffset = 0;

  Future<void> openFile(String relativePath, {required int startOffset}) async {
    throw UnsupportedError('Receiving files requires dart:io (desktop host)');
  }

  Future<void> writeChunk(int offset, Uint8List data) async {
    throw UnsupportedError('Receiving files requires dart:io (desktop host)');
  }

  Future<String?> hashOpenPrefix(int length) async => null;

  Future<String?> hashFile(String relativePath) async => null;

  Future<void> truncateTo(int length) async {}

  Future<void> close() async {}

  static String sanitizeRelative(String relativePath) {
    final normalized = relativePath.replaceAll('\\', '/');
    if (normalized.startsWith('../') ||
        normalized == '..' ||
        normalized.startsWith('/')) {
      throw ArgumentError('Unsafe relative path: $relativePath');
    }
    return normalized;
  }
}

class PathFileSource implements LocalFileSource {
  PathFileSource({required this.absolutePath, required this.entry});

  final String absolutePath;

  @override
  final FileEntry entry;

  @override
  Future<Uint8List> readAt(int offset, int length) async {
    throw UnsupportedError('PathFileSource requires dart:io');
  }

  @override
  Stream<List<int>> openRead() {
    throw UnsupportedError('PathFileSource requires dart:io');
  }
}
