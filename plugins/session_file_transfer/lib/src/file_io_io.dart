import 'dart:io';
import 'dart:typed_data';

import 'package:path/path.dart' as p;

import 'hashing.dart';
import 'local_source.dart';
import 'protocol.dart';

/// Default receive root for desktop hosts.
String defaultReceiveRoot() {
  final home = Platform.environment['HOME'] ??
      Platform.environment['USERPROFILE'] ??
      Directory.systemTemp.path;
  return p.join(home, 'Downloads', 'CloudPlayPlusTransfers');
}

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

/// Builds a flat file list from one or more local paths (files and folders).
/// Always streams sha256 when [hashContent] is true (no size cap).
Future<List<LocalFileSource>> buildManifestFromPaths(
  List<String> paths, {
  bool hashContent = true,
}) async {
  final out = <LocalFileSource>[];
  for (final path in paths) {
    final entity = FileSystemEntity.typeSync(path);
    if (entity == FileSystemEntityType.file) {
      out.add(await _fromFile(File(path), p.basename(path), hashContent));
    } else if (entity == FileSystemEntityType.directory) {
      final root = Directory(path);
      final rootName = p.basename(path);
      await for (final entity in root.list(recursive: true, followLinks: false)) {
        if (entity is! File) continue;
        final rel = p.join(rootName, p.relative(entity.path, from: path));
        out.add(await _fromFile(entity, rel.replaceAll('\\', '/'), hashContent));
      }
    } else {
      throw FileSystemException('Path not found or unsupported', path);
    }
  }
  if (out.isEmpty) {
    throw StateError('No files selected');
  }
  return out;
}

Future<PathFileSource> _fromFile(
  File file,
  String relativePath,
  bool hashContent,
) async {
  final length = await file.length();
  String? hash;
  if (hashContent) {
    hash = await Sha256Hasher.hashStream(file.openRead());
  }
  return PathFileSource(
    absolutePath: file.path,
    entry: FileEntry(
      relativePath: relativePath.replaceAll('\\', '/'),
      size: length,
      sha256: hash,
    ),
  );
}

class PathFileSource implements LocalFileSource {
  PathFileSource({required this.absolutePath, required this.entry});

  final String absolutePath;

  @override
  final FileEntry entry;

  @override
  Future<Uint8List> readAt(int offset, int length) async {
    final raf = await File(absolutePath).open(mode: FileMode.read);
    try {
      await raf.setPosition(offset);
      final buf = Uint8List(length);
      final read = await raf.readInto(buf);
      if (read <= 0) return Uint8List(0);
      if (read == length) return buf;
      return Uint8List.sublistView(buf, 0, read);
    } finally {
      await raf.close();
    }
  }

  @override
  Stream<List<int>> openRead() => File(absolutePath).openRead();
}

/// Writes received bytes under [rootDir], creating parent folders as needed.
class FileReceiveWriter {
  final String rootDir;
  RandomAccessFile? _raf;
  File? _file;
  String? _openRelPath;
  int _expectedOffset = 0;

  FileReceiveWriter(this.rootDir);

  Future<void> openFile(String relativePath, {required int startOffset}) async {
    await close();
    final safe = sanitizeRelative(relativePath);
    final target = File(p.join(rootDir, safe));
    await target.parent.create(recursive: true);
    _file = target;

    if (startOffset <= 0) {
      _raf = await target.open(mode: FileMode.write);
      _expectedOffset = 0;
    } else {
      if (!await target.exists()) {
        throw StateError('Cannot resume: missing partial file for $safe');
      }
      final length = await target.length();
      if (length < startOffset) {
        throw StateError(
            'Cannot resume: local file shorter than resume offset ($length < $startOffset)');
      }
      if (length > startOffset) {
        // Do NOT use FileMode.write — it truncates to 0 on open.
        final raf = await target.open(mode: FileMode.append);
        await raf.truncate(startOffset);
        await raf.close();
      }
      _raf = await target.open(mode: FileMode.append);
      _expectedOffset = startOffset;
    }
    _openRelPath = safe;
  }

  Future<void> writeChunk(int offset, Uint8List data) async {
    if (_raf == null) {
      throw StateError('No file open for receive');
    }
    if (offset < _expectedOffset) {
      final skip = _expectedOffset - offset;
      if (skip >= data.length) return;
      data = Uint8List.sublistView(data, skip);
      offset = _expectedOffset;
    }
    if (offset > _expectedOffset) {
      throw StateError(
          'Chunk offset gap: expected $_expectedOffset got $offset');
    }
    await _raf!.writeFrom(data);
    _expectedOffset += data.length;
  }

  /// Streaming hash of bytes `[0, length)` on disk.
  Future<String?> hashOpenPrefix(int length) async {
    final file = _file;
    if (file == null || !await file.exists()) return null;
    if (length <= 0) return Sha256Hasher.hashBytes(Uint8List(0));
    await _raf?.flush();
    return Sha256Hasher.hashStream(file.openRead(0, length));
  }

  Future<String?> hashFile(String relativePath) async {
    final safe = sanitizeRelative(relativePath);
    final file = File(p.join(rootDir, safe));
    if (!await file.exists()) return null;
    return Sha256Hasher.hashStream(file.openRead());
  }

  Future<void> truncateTo(int length) async {
    final file = _file;
    final rel = _openRelPath;
    if (file == null || rel == null) return;
    await close();
    final raf = await file.open(mode: FileMode.append);
    await raf.truncate(length);
    await raf.close();
    await openFile(rel, startOffset: length);
  }

  int get expectedOffset => _expectedOffset;

  String? get openRelPath => _openRelPath;

  Future<void> close() async {
    await _raf?.flush();
    await _raf?.close();
    _raf = null;
    _openRelPath = null;
    _file = null;
  }

  static String sanitizeRelative(String relativePath) {
    final normalized = p.normalize(relativePath.replaceAll('\\', '/'));
    if (normalized.startsWith('../') ||
        normalized == '..' ||
        p.isAbsolute(normalized)) {
      throw ArgumentError('Unsafe relative path: $relativePath');
    }
    return normalized;
  }
}
