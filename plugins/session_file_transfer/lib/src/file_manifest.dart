import 'dart:io';
import 'dart:typed_data';

import 'package:crypto/crypto.dart';
import 'package:path/path.dart' as p;

import 'protocol.dart';

/// Builds a flat file list from one or more local paths (files and folders).
class FileManifestBuilder {
  /// When true, compute sha256 for every file. Expensive for large trees;
  /// default hashes only files ≤ [hashMaxBytes].
  final int hashMaxBytes;

  FileManifestBuilder({this.hashMaxBytes = 4 * 1024 * 1024});

  Future<List<LocalFileSource>> build(List<String> paths) async {
    final out = <LocalFileSource>[];
    for (final path in paths) {
      final entity = FileSystemEntity.typeSync(path);
      if (entity == FileSystemEntityType.file) {
        out.add(await _fromFile(File(path), p.basename(path)));
      } else if (entity == FileSystemEntityType.directory) {
        final root = Directory(path);
        final rootName = p.basename(path);
        await for (final entity in root.list(recursive: true, followLinks: false)) {
          if (entity is! File) continue;
          final rel = p.join(rootName, p.relative(entity.path, from: path));
          out.add(await _fromFile(entity, rel.replaceAll('\\', '/')));
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

  Future<LocalFileSource> _fromFile(File file, String relativePath) async {
    final length = await file.length();
    String? hash;
    if (length <= hashMaxBytes) {
      hash = (await sha256.bind(file.openRead()).first).toString();
    }
    return LocalFileSource(
      absolutePath: file.path,
      entry: FileEntry(
        relativePath: relativePath.replaceAll('\\', '/'),
        size: length,
        sha256: hash,
      ),
    );
  }
}

class LocalFileSource {
  final String absolutePath;
  final FileEntry entry;

  const LocalFileSource({
    required this.absolutePath,
    required this.entry,
  });
}

/// Writes received bytes under [rootDir], creating parent folders as needed.
class FileReceiveWriter {
  final String rootDir;
  RandomAccessFile? _raf;
  String? _openRelPath;
  int _expectedOffset = 0;

  FileReceiveWriter(this.rootDir);

  Future<void> openFile(String relativePath, {required int startOffset}) async {
    await close();
    final safe = sanitizeRelative(relativePath);
    final target = File(p.join(rootDir, safe));
    await target.parent.create(recursive: true);

    if (startOffset <= 0) {
      // Truncate / create.
      _raf = await target.open(mode: FileMode.write);
      _expectedOffset = 0;
    } else {
      // Resume: append-only so we never truncate a partial file.
      // dart:io has no portable non-truncating random write mode; ordered
      // append matches our in-order chunk protocol.
      if (!await target.exists()) {
        throw StateError(
            'Cannot resume: missing partial file for $safe');
      }
      final length = await target.length();
      if (length != startOffset) {
        // Prefer on-disk length as source of truth if it is behind the ledger.
        if (length < startOffset) {
          throw StateError(
              'Cannot resume: local file shorter than resume offset ($length < $startOffset)');
        }
        // If file is ahead of ledger, truncate by rewriting prefix — rare;
        // keep bytes and continue from length instead.
      }
      _raf = await target.open(mode: FileMode.append);
      _expectedOffset = length;
    }
    _openRelPath = safe;
  }

  Future<void> writeChunk(int offset, Uint8List data) async {
    if (_raf == null) {
      throw StateError('No file open for receive');
    }
    if (offset < _expectedOffset) {
      // Duplicate / rewind chunk after reconnect — skip already-written bytes.
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

  int get expectedOffset => _expectedOffset;

  String? get openRelPath => _openRelPath;

  Future<void> close() async {
    await _raf?.close();
    _raf = null;
    _openRelPath = null;
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

/// Default receive root for desktop hosts.
String defaultReceiveRoot() {
  final home = Platform.environment['HOME'] ??
      Platform.environment['USERPROFILE'] ??
      Directory.systemTemp.path;
  return p.join(home, 'Downloads', 'CloudPlayPlusTransfers');
}
