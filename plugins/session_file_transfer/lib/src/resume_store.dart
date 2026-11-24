import 'dart:convert';
import 'dart:io';

import 'package:path/path.dart' as p;

import 'protocol.dart';

/// Lightweight on-disk resume ledger for incomplete incoming transfers.
///
/// Scope: same device, same [rootDir]. Survives mid-session abort and
/// app restart **if** the peer re-offers the same [transferId] (or
/// matching size+sha256). Cross-session peer identity is not attested —
/// treat resume as best-effort (see package README gaps).
class ResumeStore {
  final String rootDir;

  ResumeStore(this.rootDir);

  File get _ledgerFile =>
      File(p.join(rootDir, '.cpp_file_xfer_resume.json'));

  Future<Map<String, dynamic>> _read() async {
    final file = _ledgerFile;
    if (!await file.exists()) return {};
    try {
      final decoded = jsonDecode(await file.readAsString());
      if (decoded is Map) return Map<String, dynamic>.from(decoded);
    } catch (_) {}
    return {};
  }

  Future<void> _write(Map<String, dynamic> data) async {
    await Directory(rootDir).create(recursive: true);
    await _ledgerFile.writeAsString(jsonEncode(data));
  }

  Future<void> saveProgress({
    required String transferId,
    required List<FileEntry> files,
    required int fileIndex,
    required int resumeOffset,
  }) async {
    final data = await _read();
    data[transferId] = {
      'files': files.map((e) => e.toJson()).toList(),
      'fileIndex': fileIndex,
      'resumeOffset': resumeOffset,
      'updatedAtMs': DateTime.now().millisecondsSinceEpoch,
    };
    await _write(data);
  }

  Future<ResumeCheckpoint?> lookup(String transferId) async {
    final data = await _read();
    final entry = data[transferId];
    if (entry is! Map) return null;
    final map = Map<String, dynamic>.from(entry);
    final rawFiles = map['files'] as List? ?? const [];
    return ResumeCheckpoint(
      transferId: transferId,
      files: rawFiles
          .map((e) => FileEntry.fromJson(Map<String, dynamic>.from(e as Map)))
          .toList(),
      fileIndex: (map['fileIndex'] as num?)?.toInt() ?? 0,
      resumeOffset: (map['resumeOffset'] as num?)?.toInt() ?? 0,
    );
  }

  /// Match by transferId first; else by identical file list sizes (+ sha when present).
  Future<ResumeCheckpoint?> findCompatible(List<FileEntry> offer) async {
    final data = await _read();
    for (final entry in data.entries) {
      final map = Map<String, dynamic>.from(entry.value as Map);
      final rawFiles = map['files'] as List? ?? const [];
      final files = rawFiles
          .map((e) => FileEntry.fromJson(Map<String, dynamic>.from(e as Map)))
          .toList();
      if (!_sameManifest(files, offer)) continue;
      return ResumeCheckpoint(
        transferId: entry.key,
        files: files,
        fileIndex: (map['fileIndex'] as num?)?.toInt() ?? 0,
        resumeOffset: (map['resumeOffset'] as num?)?.toInt() ?? 0,
      );
    }
    return null;
  }

  Future<void> clear(String transferId) async {
    final data = await _read();
    data.remove(transferId);
    await _write(data);
  }

  static bool _sameManifest(List<FileEntry> a, List<FileEntry> b) {
    if (a.length != b.length) return false;
    for (var i = 0; i < a.length; i++) {
      if (a[i].relativePath != b[i].relativePath) return false;
      if (a[i].size != b[i].size) return false;
      if (a[i].sha256 != null &&
          b[i].sha256 != null &&
          a[i].sha256 != b[i].sha256) {
        return false;
      }
    }
    return true;
  }
}

class ResumeCheckpoint {
  final String transferId;
  final List<FileEntry> files;
  final int fileIndex;
  final int resumeOffset;

  const ResumeCheckpoint({
    required this.transferId,
    required this.files,
    required this.fileIndex,
    required this.resumeOffset,
  });
}
