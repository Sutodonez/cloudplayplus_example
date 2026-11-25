import 'dart:typed_data';

import 'file_io.dart';
import 'local_source.dart';

export 'local_source.dart';

/// Builds a flat file list from local paths and/or in-memory blobs.
///
/// Always streams sha256 when [hashContent] is true — no size cap
/// (chunked hashing keeps peak memory bounded for path-backed files).
class FileManifestBuilder {
  final bool hashContent;

  FileManifestBuilder({this.hashContent = true});

  Future<List<LocalFileSource>> build(List<String> paths) =>
      buildManifestFromPaths(paths, hashContent: hashContent);

  Future<List<LocalFileSource>> buildFromNamedBytes(
    List<({String relativePath, Uint8List bytes})> files,
  ) =>
      buildManifestFromNamedBytes(files, hashContent: hashContent);
}
