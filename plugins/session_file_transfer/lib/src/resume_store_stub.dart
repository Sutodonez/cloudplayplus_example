import 'protocol.dart';

/// In-memory resume ledger (Web / tests without filesystem).
class ResumeStore {
  ResumeStore(this.rootDir);

  final String rootDir;
  final Map<String, Map<String, dynamic>> _data = {};

  Future<void> saveProgress({
    required String transferId,
    required List<FileEntry> files,
    required int fileIndex,
    required int resumeOffset,
    String? prefixSha256,
    String? contentFingerprint,
  }) async {
    final prev = _data[transferId];
    String? keepPrefix = prefixSha256;
    String? keepFp = contentFingerprint;
    if (prev != null) {
      keepPrefix ??= prev['prefixSha256'] as String?;
      keepFp ??= prev['contentFingerprint'] as String?;
    }
    _data[transferId] = {
      'files': files.map((e) => e.toJson()).toList(),
      'fileIndex': fileIndex,
      'resumeOffset': resumeOffset,
      if (keepPrefix != null) 'prefixSha256': keepPrefix,
      if (keepFp != null) 'contentFingerprint': keepFp,
      'updatedAtMs': DateTime.now().millisecondsSinceEpoch,
    };
  }

  Future<ResumeCheckpoint?> lookup(String transferId) async {
    final map = _data[transferId];
    if (map == null) return null;
    return _fromMap(transferId, map);
  }

  Future<ResumeCheckpoint?> findCompatible(
    List<FileEntry> offer, {
    String? contentFingerprint,
  }) async {
    for (final entry in _data.entries) {
      final map = entry.value;
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
    _data.remove(transferId);
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
