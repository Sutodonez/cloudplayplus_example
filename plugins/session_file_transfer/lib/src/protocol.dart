/// Binary opcode for file payload chunks on the reliable data channel.
/// Placed after CloudPlayPlus audio opcodes (65/66); keep in sync with
/// `lib/entities/messages.dart` (`LP_FILE_CHUNK`).
const int kFileChunkOpcode = 67;

/// JSON envelope root key for control messages (offer/accept/resume/…).
const String kFileXferJsonKey = 'file_xfer';

/// Receiver-side caps for control envelopes / offers (post-merge plugin review).
abstract final class FileXferLimits {
  /// Max UTF-8 bytes for a single control JSON text frame.
  static const int maxControlJsonBytes = 1024 * 1024;

  /// Max number of files declared in one offer / resume query.
  static const int maxFilesPerOffer = 4096;

  /// Max sum of declared file sizes across one offer.
  static const int maxTotalDeclaredBytes = 1024 * 1024 * 1024 * 1024; // 1 TiB

  /// Hex sha256 length (32 bytes → 64 hex chars).
  static const int sha256HexLength = 64;
}

/// Control operations.
abstract final class FileXferOp {
  static const String offer = 'offer';
  static const String accept = 'accept';
  static const String reject = 'reject';
  static const String abort = 'abort';
  static const String complete = 'complete';
  static const String progress = 'progress';
  static const String resumeQuery = 'resume_query';
  static const String resumeAck = 'resume_ack';
  /// Sender detected prefix mismatch; receiver must truncate and restart
  /// from [FileXferControl.fileIndex] / [FileXferControl.resumeOffset].
  static const String resumeRestart = 'resume_restart';
}

/// One file entry inside an offer / resume ack.
class FileEntry {
  final String relativePath;
  final int size;
  /// Content hash (sha256 hex). Always preferred for resume identity.
  final String? sha256;

  const FileEntry({
    required this.relativePath,
    required this.size,
    this.sha256,
  });

  Map<String, dynamic> toJson() => {
        'path': relativePath,
        'size': size,
        if (sha256 != null) 'sha256': sha256,
      };

  factory FileEntry.fromJson(Map<String, dynamic> json) => FileEntry(
        relativePath: json['path'] as String,
        size: (json['size'] as num).toInt(),
        sha256: json['sha256'] as String?,
      );
}

/// Control message carried as `{"file_xfer": ...}` JSON text.
class FileXferControl {
  final String op;
  final String transferId;
  final List<FileEntry> files;
  final int fileIndex;
  /// Bytes already received for [fileIndex] (resume / progress).
  final int resumeOffset;
  /// Aggregate bytes transferred across the whole offer.
  final int bytesTransferred;
  final int bytesTotal;
  final String? error;
  final String? saveRootHint;
  /// SHA-256 of bytes `[0, resumeOffset)` on the receiving side (resume verify).
  final String? prefixSha256;
  /// Stable fingerprint of the offered manifest (path+size+sha lines).
  final String? contentFingerprint;

  const FileXferControl({
    required this.op,
    required this.transferId,
    this.files = const [],
    this.fileIndex = 0,
    this.resumeOffset = 0,
    this.bytesTransferred = 0,
    this.bytesTotal = 0,
    this.error,
    this.saveRootHint,
    this.prefixSha256,
    this.contentFingerprint,
  });

  Map<String, dynamic> toEnvelope() => {
        kFileXferJsonKey: {
          'op': op,
          'transferId': transferId,
          if (files.isNotEmpty) 'files': files.map((e) => e.toJson()).toList(),
          'fileIndex': fileIndex,
          'resumeOffset': resumeOffset,
          'bytesTransferred': bytesTransferred,
          'bytesTotal': bytesTotal,
          if (error != null) 'error': error,
          if (saveRootHint != null) 'saveRootHint': saveRootHint,
          if (prefixSha256 != null) 'prefixSha256': prefixSha256,
          if (contentFingerprint != null)
            'contentFingerprint': contentFingerprint,
        },
      };

  factory FileXferControl.fromEnvelope(Map<String, dynamic> envelope) {
    final body = envelope[kFileXferJsonKey];
    if (body is! Map) {
      throw FormatException('missing $kFileXferJsonKey');
    }
    final map = Map<String, dynamic>.from(body);
    final rawFiles = map['files'] as List? ?? const [];
    return FileXferControl(
      op: map['op'] as String,
      transferId: map['transferId'] as String,
      files: rawFiles
          .map((e) => FileEntry.fromJson(Map<String, dynamic>.from(e as Map)))
          .toList(),
      fileIndex: (map['fileIndex'] as num?)?.toInt() ?? 0,
      resumeOffset: (map['resumeOffset'] as num?)?.toInt() ?? 0,
      bytesTransferred: (map['bytesTransferred'] as num?)?.toInt() ?? 0,
      bytesTotal: (map['bytesTotal'] as num?)?.toInt() ?? 0,
      error: map['error'] as String?,
      saveRootHint: map['saveRootHint'] as String?,
      prefixSha256: map['prefixSha256'] as String?,
      contentFingerprint: map['contentFingerprint'] as String?,
    );
  }
}

/// Progress snapshot for UI.
class FileTransferProgress {
  final String transferId;
  final FileTransferState state;
  final int bytesTransferred;
  final int bytesTotal;
  final int fileIndex;
  final int fileCount;
  final String? currentPath;
  final String? error;
  final bool isIncoming;

  const FileTransferProgress({
    required this.transferId,
    required this.state,
    required this.bytesTransferred,
    required this.bytesTotal,
    required this.fileIndex,
    required this.fileCount,
    this.currentPath,
    this.error,
    this.isIncoming = false,
  });

  double get fraction {
    if (bytesTotal <= 0) return 0;
    return (bytesTransferred / bytesTotal).clamp(0.0, 1.0);
  }
}

enum FileTransferState {
  idle,
  offering,
  transferring,
  paused,
  completed,
  aborted,
  failed,
}
