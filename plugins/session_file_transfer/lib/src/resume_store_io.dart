import 'dart:convert';
import 'dart:io';

import 'package:path/path.dart' as p;

import 'protocol.dart';

/// On-disk resume ledger for incomplete incoming transfers.
///
/// Survives mid-session abort and app restart when the peer re-offers the
/// same [transferId] or a matching content fingerprint / size+sha256
/// manifest. Prefix SHA-256 lets the sender verify partial bytes before
/// continuing (closer to UU-style 断点续传 than offset-only ledgers).
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
    String? prefixSha256,
    String? contentFingerprint,
  }) async {
    final data = await _read();
    final prev = data[transferId];
    String? keepPrefix = prefixSha256;
    String? keepFp = contentFingerprint;
    if (prev is Map) {
      keepPrefix ??= prev['prefixSha256'] as String?;
      keepFp ??= prev['contentFingerprint'] as String?;
    }
    data[transferId] = {
      'files': files.map((e) => e.toJson()).toList(),
      'fileIndex': fileIndex,
      'resumeOffset': resumeOffset,
      if (keepPrefix != null) 'prefixSha256': keepPrefix,
      if (keepFp != null) 'contentFingerprint': keepFp,
      'updatedAtMs': DateTime.now().millisecondsSinceEpoch,
    };
    await _write(data);
  }

  Future<ResumeCheckpoint?> lookup(String transferId) async {
    final data = await _read();
    final entry = data[transferId];
    if (entry is! Map) return null;
    return _fromMap(transferId, Map<String, dynamic>.from(entry));
  }

  /// Match by transferId first (caller); else fingerprint, else size+sha list.
  Future<ResumeCheckpoint?> findCompatible(
    List<FileEntry> offer, {
    String? contentFingerprint,
  }) async {
    final data = await _read();
    for (final entry in data.entries) {
      final map = Map<String, dynamic>.from(entry.value as Map);
      final rawFiles = map['files'] as List? ?? const [];
      final files = rawFiles
          .map((e) => FileEntry.fromJson(Map<String, dynamic>.from(e as Map)))
          .toList();
      final fp = map['contentFingerprint'] as String?;
      if (contentFingerprint != null &&
          fp != null &&
          contentFingerprint == fp) {
        return _fromMap(entry.key, map);
      }
      if (!_sameManifest(files, offer)) continue;
      return _fromMap(entry.key, map);
    }
    return null;
  }

  Future<void> clear(String transferId) async {
    final data = await _read();
    data.remove(transferId);
    await _write(data);
  }

  static ResumeCheckpoint _fromMap(String id, Map<String, dynamic> map) {
    final rawFiles = map['files'] as List? ?? const [];
    return ResumeCheckpoint(
      transferId: id,
      files: rawFiles
          .map((e) => FileEntry.fromJson(Map<String, dynamic>.from(e as Map)))
          .toList(),
      fileIndex: (map['fileIndex'] as num?)?.toInt() ?? 0,
      resumeOffset: (map['resumeOffset'] as num?)?.toInt() ?? 0,
      prefixSha256: map['prefixSha256'] as String?,
      contentFingerprint: map['contentFingerprint'] as String?,
    );
  }

  static bool _sameManifest(List<FileEntry> a, List<FileEntry> b) {
    if (a.length != b.length) return false;
    for (var i = 0; i < a.length; i++) {
      if (a[i].relativePath != b[i].relativePath) return false;
      if (a[i].size != b[i].size) return false;
      // Prefer strong identity: when both sides have sha, they must match.
      if (a[i].sha256 != null &&
          b[i].sha256 != null &&
          a[i].sha256 != b[i].sha256) {
        return false;
      }
      // If offer has sha but ledger entry lacks it (legacy), still allow
      // size+path match; prefix verify will catch corruption.
    }
    return true;
  }
}

class ResumeCheckpoint {
  final String transferId;
  final List<FileEntry> files;
  final int fileIndex;
  final int resumeOffset;
  final String? prefixSha256;
  final String? contentFingerprint;

  const ResumeCheckpoint({
    required this.transferId,
    required this.files,
    required this.fileIndex,
    required this.resumeOffset,
    this.prefixSha256,
    this.contentFingerprint,
  });
}
