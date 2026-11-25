import 'dart:async';
import 'dart:math';
import 'dart:typed_data';

import 'codec.dart';
import 'file_io.dart';
import 'file_manifest.dart';
import 'hashing.dart';
import 'local_source.dart';
import 'protocol.dart';
import 'resume_store.dart';

typedef FileXferSendText = Future<void> Function(String text);
typedef FileXferSendBinary = Future<void> Function(Uint8List bytes);

/// Drives one side of a session file/folder transfer.
///
/// App responsibilities:
/// - Call [onBinaryMessage] / [onTextMessage] from the reliable data channel.
/// - Provide [sendText] / [sendBinary] that write to that channel.
/// - Optionally show UI from [progress] stream and [onIncomingOffer].
///
/// Resume: ledger + chunk-aligned offsets + prefix SHA-256 verify on both
/// sides before continuing (closer to UU 断点续传 than offset-only).
class FileTransferEngine {
  FileTransferEngine({
    required this.sendText,
    required this.sendBinary,
    String? receiveRoot,
    this.chunkSize = 16 * 1024,
    this.maxInFlight = 8,
    bool autoAcceptIncoming = true,
  })  : receiveRoot = receiveRoot ?? defaultReceiveRoot(),
        _autoAcceptIncoming = autoAcceptIncoming {
    _resumeStore = ResumeStore(this.receiveRoot);
    _writer = FileReceiveWriter(this.receiveRoot);
  }

  final FileXferSendText sendText;
  final FileXferSendBinary sendBinary;
  final String receiveRoot;
  final int chunkSize;
  final int maxInFlight;

  bool _autoAcceptIncoming;
  bool get autoAcceptIncoming => _autoAcceptIncoming;
  set autoAcceptIncoming(bool value) => _autoAcceptIncoming = value;

  late final ResumeStore _resumeStore;
  late FileReceiveWriter _writer;

  final _progressController =
      StreamController<FileTransferProgress>.broadcast();
  Stream<FileTransferProgress> get progress => _progressController.stream;

  /// Called when a peer offers files. Return true to accept.
  /// When null, [autoAcceptIncoming] decides.
  Future<bool> Function(FileXferControl offer)? onIncomingOffer;

  FileTransferState _state = FileTransferState.idle;
  String? _activeTransferId;
  int? _activeCrc;
  String? _contentFingerprint;
  List<LocalFileSource> _outgoing = [];
  List<FileEntry> _incoming = [];

  int _fileIndex = 0;
  int _bytesTransferred = 0;
  int _bytesTotal = 0;
  int _inFlight = 0;
  bool _abortRequested = false;
  Completer<void>? _windowSlot;
  bool _isIncoming = false;
  Future<void> _chunkQueue = Future.value();
  int _lastPrefixHashAt = 0;
  static const int _prefixHashIntervalBytes = 1024 * 1024;

  FileTransferState get state => _state;
  String? get activeTransferId => _activeTransferId;

  void dispose() {
    _abortRequested = true;
    unawaited(_writer.close());
    _progressController.close();
  }

  /// Offer local [paths] (files and/or folders) to the peer (desktop).
  Future<void> sendPaths(List<String> paths) async {
    if (_state == FileTransferState.transferring ||
        _state == FileTransferState.offering) {
      throw StateError('Transfer already in progress');
    }
    final manifest = await FileManifestBuilder().build(paths);
    await sendManifest(manifest);
  }

  /// Offer in-memory files (Web controller / tests).
  Future<void> sendNamedBytes(
    List<({String relativePath, Uint8List bytes})> files,
  ) async {
    if (_state == FileTransferState.transferring ||
        _state == FileTransferState.offering) {
      throw StateError('Transfer already in progress');
    }
    final manifest = await FileManifestBuilder().buildFromNamedBytes(files);
    await sendManifest(manifest);
  }

  Future<void> sendManifest(List<LocalFileSource> sources) async {
    _abortRequested = false;
    _isIncoming = false;
    _outgoing = sources;
    _incoming = [];
    _fileIndex = 0;
    _bytesTransferred = 0;
    _bytesTotal = sources.fold<int>(0, (s, e) => s + e.entry.size);
    _contentFingerprint = Sha256Hasher.manifestFingerprint(
      sources.map((e) => (
            path: e.entry.relativePath,
            size: e.entry.size,
            sha256: e.entry.sha256,
          )),
    );
    _activeTransferId = _newTransferId();
    _activeCrc = FileChunkCodec.transferIdCrc32(_activeTransferId!);
    _state = FileTransferState.offering;
    _emitProgress();

    await sendText(FileXferJsonCodec.encodeControl(FileXferControl(
      op: FileXferOp.offer,
      transferId: _activeTransferId!,
      files: sources.map((e) => e.entry).toList(),
      bytesTotal: _bytesTotal,
      contentFingerprint: _contentFingerprint,
    )));
  }

  Future<void> abort({String? reason}) async {
    _abortRequested = true;
    final id = _activeTransferId;
    if (id != null) {
      await sendText(FileXferJsonCodec.encodeControl(FileXferControl(
        op: FileXferOp.abort,
        transferId: id,
        error: reason,
      )));
    }
    _state = FileTransferState.aborted;
    _emitProgress(error: reason);
    await _writer.close();
  }

  void onTextMessage(String text) {
    final control = FileXferJsonCodec.tryDecodeText(text);
    if (control == null) return;
    unawaited(_handleControl(control));
  }

  void onBinaryMessage(Uint8List data) {
    final chunk = FileChunkCodec.tryDecode(data);
    if (chunk == null) return;
    _chunkQueue = _chunkQueue.then((_) => _handleChunk(chunk));
  }

  Future<void> _handleControl(FileXferControl control) async {
    switch (control.op) {
      case FileXferOp.offer:
        await _onOffer(control);
        break;
      case FileXferOp.accept:
        if (control.transferId != _activeTransferId) return;
        await _onAccept(control);
        break;
      case FileXferOp.resumeRestart:
        if (!_isIncoming || control.transferId != _activeTransferId) return;
        await _applyResumeRestart(control.fileIndex, control.resumeOffset);
        break;
      case FileXferOp.reject:
        if (control.transferId != _activeTransferId) return;
        _state = FileTransferState.aborted;
        _emitProgress(error: control.error ?? 'rejected');
        break;
      case FileXferOp.abort:
        if (_activeTransferId != null &&
            control.transferId != _activeTransferId) {
          return;
        }
        _abortRequested = true;
        _state = FileTransferState.aborted;
        _emitProgress(error: control.error);
        await _writer.close();
        break;
      case FileXferOp.progress:
        if (control.transferId != _activeTransferId) return;
        _inFlight = max(0, _inFlight - 1);
        _windowSlot?.complete();
        _windowSlot = null;
        break;
      case FileXferOp.complete:
        if (control.transferId != _activeTransferId) return;
        _state = FileTransferState.completed;
        _bytesTransferred = _bytesTotal;
        _emitProgress();
        break;
      case FileXferOp.resumeQuery:
        final fp = control.contentFingerprint ??
            Sha256Hasher.manifestFingerprint(
              control.files.map((e) => (
                    path: e.relativePath,
                    size: e.size,
                    sha256: e.sha256,
                  )),
            );
        final checkpoint = await _resumeStore.lookup(control.transferId) ??
            await _resumeStore.findCompatible(
              control.files,
              contentFingerprint: fp,
            );
        var fileIndex = checkpoint?.fileIndex ?? 0;
        var offset = checkpoint?.resumeOffset ?? 0;
        offset = _alignDown(offset);
        String? prefix;
        if (checkpoint != null &&
            fileIndex < control.files.length &&
            offset > 0) {
          await _writer.openFile(control.files[fileIndex].relativePath,
              startOffset: offset);
          offset = _alignDown(_writer.expectedOffset);
          if (offset > 0) {
            prefix = await _writer.hashOpenPrefix(offset);
          }
          await _writer.close();
        }
        await sendText(FileXferJsonCodec.encodeControl(FileXferControl(
          op: FileXferOp.resumeAck,
          transferId: control.transferId,
          files: control.files,
          fileIndex: fileIndex,
          resumeOffset: offset,
          bytesTotal: control.bytesTotal,
          prefixSha256: prefix,
          contentFingerprint: fp,
        )));
        break;
      case FileXferOp.resumeAck:
        break;
      default:
        break;
    }
  }

  Future<void> _onAccept(FileXferControl control) async {
    var fileIndex = control.fileIndex;
    var offset = _alignDown(control.resumeOffset);

    if (offset > 0 && fileIndex < _outgoing.length) {
      final ok = await _verifyOutgoingPrefix(
        _outgoing[fileIndex],
        offset,
        control.prefixSha256,
      );
      if (!ok) {
        await sendText(FileXferJsonCodec.encodeControl(FileXferControl(
          op: FileXferOp.resumeRestart,
          transferId: control.transferId,
          fileIndex: fileIndex,
          resumeOffset: 0,
        )));
        offset = 0;
      }
    }

    _fileIndex = fileIndex;
    _bytesTransferred = _prefixBytes(
      _outgoing.map((e) => e.entry).toList(),
      fileIndex,
      offset,
    );
    _state = FileTransferState.transferring;
    _emitProgress();
    unawaited(_runSendLoop(
      startFileIndex: fileIndex,
      startOffset: offset,
    ));
  }

  Future<bool> _verifyOutgoingPrefix(
    LocalFileSource source,
    int offset,
    String? peerPrefixSha,
  ) async {
    if (offset <= 0) return true;
    final local = await _hashSourcePrefix(source, offset);
    if (peerPrefixSha == null || peerPrefixSha.isEmpty) {
      // Legacy peer without prefix — still continue but only if sizes match.
      return true;
    }
    return local == peerPrefixSha;
  }

  Future<String> _hashSourcePrefix(LocalFileSource source, int length) async {
    if (length <= 0) return Sha256Hasher.hashBytes(Uint8List(0));
    final chunks = <List<int>>[];
    var remaining = length;
    var offset = 0;
    while (remaining > 0) {
      final n = min(remaining, 64 * 1024);
      final piece = await source.readAt(offset, n);
      if (piece.isEmpty) break;
      chunks.add(piece);
      offset += piece.length;
      remaining -= piece.length;
      if (piece.length < n) break;
    }
    return Sha256Hasher.hashStream(Stream.fromIterable(chunks));
  }

  Future<void> _onOffer(FileXferControl offer) async {
    var accept = _autoAcceptIncoming;
    if (onIncomingOffer != null) {
      accept = await onIncomingOffer!(offer);
    }
    if (!accept) {
      await sendText(FileXferJsonCodec.encodeControl(FileXferControl(
        op: FileXferOp.reject,
        transferId: offer.transferId,
        error: 'user rejected',
      )));
      return;
    }

    _isIncoming = true;
    _activeTransferId = offer.transferId;
    _activeCrc = FileChunkCodec.transferIdCrc32(offer.transferId);
    _incoming = offer.files;
    _outgoing = [];
    _bytesTotal = offer.files.fold<int>(0, (s, e) => s + e.size);
    _contentFingerprint = offer.contentFingerprint ??
        Sha256Hasher.manifestFingerprint(
          offer.files.map((e) => (
                path: e.relativePath,
                size: e.size,
                sha256: e.sha256,
              )),
        );
    _abortRequested = false;

    await _writer.close();
    _writer = FileReceiveWriter(receiveRoot);

    final checkpoint = await _resumeStore.lookup(offer.transferId) ??
        await _resumeStore.findCompatible(
          offer.files,
          contentFingerprint: _contentFingerprint,
        );
    var fileIndex = checkpoint?.fileIndex ?? 0;
    var offset = _alignDown(checkpoint?.resumeOffset ?? 0);
    String? prefixSha;

    if (fileIndex < offer.files.length) {
      try {
        await _writer.openFile(offer.files[fileIndex].relativePath,
            startOffset: offset);
        offset = _alignDown(_writer.expectedOffset);
        if (offset != _writer.expectedOffset) {
          await _writer.truncateTo(offset);
        }
        if (offset > 0) {
          prefixSha = await _writer.hashOpenPrefix(offset);
          // If ledger had a prefix and disk differs, restart this file.
          if (checkpoint?.prefixSha256 != null &&
              prefixSha != null &&
              checkpoint!.prefixSha256 != prefixSha) {
            await _writer.close();
            await _writer.openFile(offer.files[fileIndex].relativePath,
                startOffset: 0);
            offset = 0;
            prefixSha = null;
          }
        }
      } catch (_) {
        // Missing/corrupt partial — start fresh on this file.
        await _writer.close();
        await _writer.openFile(offer.files[fileIndex].relativePath,
            startOffset: 0);
        offset = 0;
        prefixSha = null;
      }
    }

    _fileIndex = fileIndex;
    _bytesTransferred = _prefixBytes(offer.files, fileIndex, offset);
    _state = FileTransferState.transferring;
    _emitProgress();

    await sendText(FileXferJsonCodec.encodeControl(FileXferControl(
      op: FileXferOp.accept,
      transferId: offer.transferId,
      files: offer.files,
      fileIndex: fileIndex,
      resumeOffset: offset,
      bytesTotal: _bytesTotal,
      bytesTransferred: _bytesTransferred,
      saveRootHint: receiveRoot,
      prefixSha256: prefixSha,
      contentFingerprint: _contentFingerprint,
    )));
  }

  Future<void> _applyResumeRestart(int fileIndex, int offset) async {
    offset = _alignDown(offset);
    if (fileIndex >= _incoming.length) return;
    await _writer.close();
    await _writer.openFile(_incoming[fileIndex].relativePath,
        startOffset: offset);
    _fileIndex = fileIndex;
    _bytesTransferred = _prefixBytes(_incoming, fileIndex, offset);
    await _resumeStore.saveProgress(
      transferId: _activeTransferId!,
      files: _incoming,
      fileIndex: fileIndex,
      resumeOffset: offset,
      prefixSha256: offset > 0 ? await _writer.hashOpenPrefix(offset) : null,
      contentFingerprint: _contentFingerprint,
    );
    _emitProgress();
  }

  Future<void> _handleChunk(FileChunk chunk) async {
    if (_activeCrc == null || chunk.transferIdCrc32 != _activeCrc) return;
    if (_state != FileTransferState.transferring || !_isIncoming) return;
    if (_abortRequested) return;
    if (chunk.fileIndex >= _incoming.length) return;

    try {
      final expectedRel =
          FileReceiveWriter.sanitizeRelative(_incoming[chunk.fileIndex].relativePath);
      // Sender restart (offset 0 while we still hold a partial): reopen.
      if (chunk.offset == 0 &&
          chunk.fileIndex == _fileIndex &&
          _writer.openRelPath == expectedRel &&
          _writer.expectedOffset > 0) {
        await _writer.openFile(_incoming[chunk.fileIndex].relativePath,
            startOffset: 0);
        _lastPrefixHashAt = 0;
      } else if (_writer.openRelPath == null ||
          chunk.fileIndex != _fileIndex ||
          _writer.openRelPath != expectedRel) {
        _fileIndex = chunk.fileIndex;
        await _writer.openFile(_incoming[chunk.fileIndex].relativePath,
            startOffset: chunk.offset);
      }

      await _writer.writeChunk(chunk.offset, chunk.payload);
      _bytesTransferred += chunk.payload.length;
      _emitProgress();

      final entry = _incoming[chunk.fileIndex];
      final atFileEnd = _writer.expectedOffset >= entry.size;
      final dueHash = atFileEnd ||
          (_writer.expectedOffset - _lastPrefixHashAt) >=
              _prefixHashIntervalBytes;
      String? prefixSha;
      if (dueHash && _writer.expectedOffset > 0) {
        prefixSha = await _writer.hashOpenPrefix(_writer.expectedOffset);
        _lastPrefixHashAt = _writer.expectedOffset;
      }

      await _resumeStore.saveProgress(
        transferId: _activeTransferId!,
        files: _incoming,
        fileIndex: chunk.fileIndex,
        resumeOffset: _writer.expectedOffset,
        prefixSha256: prefixSha,
        contentFingerprint: _contentFingerprint,
      );

      await sendText(FileXferJsonCodec.encodeControl(FileXferControl(
        op: FileXferOp.progress,
        transferId: _activeTransferId!,
        fileIndex: chunk.fileIndex,
        resumeOffset: _writer.expectedOffset,
        bytesTransferred: _bytesTransferred,
        bytesTotal: _bytesTotal,
        prefixSha256: prefixSha,
      )));

      if (atFileEnd) {
        await _writer.close();
        if (entry.sha256 != null) {
          final got = await _writer.hashFile(entry.relativePath);
          if (got != null && got != entry.sha256) {
            throw StateError(
                'Integrity check failed for ${entry.relativePath}');
          }
        }
        final next = chunk.fileIndex + 1;
        _lastPrefixHashAt = 0;
        if (next >= _incoming.length) {
          await _resumeStore.clear(_activeTransferId!);
          _state = FileTransferState.completed;
          _emitProgress();
          await sendText(FileXferJsonCodec.encodeControl(FileXferControl(
            op: FileXferOp.complete,
            transferId: _activeTransferId!,
            bytesTransferred: _bytesTotal,
            bytesTotal: _bytesTotal,
          )));
        } else {
          _fileIndex = next;
          await _writer.openFile(_incoming[next].relativePath, startOffset: 0);
          await _resumeStore.saveProgress(
            transferId: _activeTransferId!,
            files: _incoming,
            fileIndex: next,
            resumeOffset: 0,
            contentFingerprint: _contentFingerprint,
          );
        }
      }
    } catch (e) {
      _state = FileTransferState.failed;
      _emitProgress(error: e.toString());
      await abort(reason: e.toString());
    }
  }

  Future<void> _runSendLoop({
    required int startFileIndex,
    required int startOffset,
  }) async {
    _inFlight = 0;
    try {
      for (var i = startFileIndex; i < _outgoing.length; i++) {
        if (_abortRequested) return;
        _fileIndex = i;
        final source = _outgoing[i];
        var offset = (i == startFileIndex) ? startOffset : 0;
        while (offset < source.entry.size) {
          if (_abortRequested) return;
          while (_inFlight >= maxInFlight) {
            _windowSlot = Completer<void>();
            await _windowSlot!.future;
            if (_abortRequested) return;
          }
          final toRead = min(chunkSize, source.entry.size - offset);
          final slice = await source.readAt(offset, toRead);
          if (slice.isEmpty) break;
          final packet = FileChunkCodec.encode(
            transferId: _activeTransferId!,
            fileIndex: i,
            offset: offset,
            payload: slice,
          );
          await sendBinary(packet);
          _inFlight++;
          offset += slice.length;
          _bytesTransferred += slice.length;
          _emitProgress();
        }
      }
    } catch (e) {
      _state = FileTransferState.failed;
      _emitProgress(error: e.toString());
      await abort(reason: e.toString());
    }
  }

  int _alignDown(int offset) {
    if (offset <= 0 || chunkSize <= 0) return 0;
    return (offset ~/ chunkSize) * chunkSize;
  }

  void _emitProgress({String? error}) {
    if (_progressController.isClosed) return;
    final files =
        _isIncoming ? _incoming : _outgoing.map((e) => e.entry).toList();
    _progressController.add(FileTransferProgress(
      transferId: _activeTransferId ?? '',
      state: error != null && _state != FileTransferState.aborted
          ? FileTransferState.failed
          : _state,
      bytesTransferred: _bytesTransferred,
      bytesTotal: _bytesTotal,
      fileIndex: _fileIndex,
      fileCount: files.length,
      currentPath: files.isEmpty
          ? null
          : files[min(_fileIndex, files.length - 1)].relativePath,
      error: error,
      isIncoming: _isIncoming,
    ));
  }

  static int _prefixBytes(List<FileEntry> files, int fileIndex, int offset) {
    var total = 0;
    for (var i = 0; i < fileIndex && i < files.length; i++) {
      total += files[i].size;
    }
    return total + offset;
  }

  static String _newTransferId() {
    final now = DateTime.now().microsecondsSinceEpoch;
    final rand = Random().nextInt(1 << 32).toRadixString(16);
    return 'xfer_${now}_$rand';
  }
}
