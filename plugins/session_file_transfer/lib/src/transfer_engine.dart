import 'dart:async';
import 'dart:io';
import 'dart:math';
import 'dart:typed_data';

import 'codec.dart';
import 'file_manifest.dart';
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
class FileTransferEngine {
  FileTransferEngine({
    required this.sendText,
    required this.sendBinary,
    String? receiveRoot,
    this.chunkSize = 16 * 1024,
    this.maxInFlight = 8,
    this.autoAcceptIncoming = true,
  }) : receiveRoot = receiveRoot ?? defaultReceiveRoot() {
    _resumeStore = ResumeStore(this.receiveRoot);
    _writer = FileReceiveWriter(this.receiveRoot);
  }

  final FileXferSendText sendText;
  final FileXferSendBinary sendBinary;
  final String receiveRoot;
  final int chunkSize;
  final int maxInFlight;
  final bool autoAcceptIncoming;

  late final ResumeStore _resumeStore;
  late FileReceiveWriter _writer;

  final _progressController =
      StreamController<FileTransferProgress>.broadcast();
  Stream<FileTransferProgress> get progress => _progressController.stream;

  /// Called when a peer offers files. Return true to accept.
  Future<bool> Function(FileXferControl offer)? onIncomingOffer;

  FileTransferState _state = FileTransferState.idle;
  String? _activeTransferId;
  int? _activeCrc;
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

  FileTransferState get state => _state;
  String? get activeTransferId => _activeTransferId;

  void dispose() {
    _abortRequested = true;
    unawaited(_writer.close());
    _progressController.close();
  }

  /// Offer local [paths] (files and/or folders) to the peer.
  Future<void> sendPaths(List<String> paths) async {
    if (_state == FileTransferState.transferring ||
        _state == FileTransferState.offering) {
      throw StateError('Transfer already in progress');
    }
    final manifest = await FileManifestBuilder().build(paths);
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
    _activeTransferId = _newTransferId();
    _activeCrc = FileChunkCodec.transferIdCrc32(_activeTransferId!);
    _state = FileTransferState.offering;
    _emitProgress();

    await sendText(FileXferJsonCodec.encodeControl(FileXferControl(
      op: FileXferOp.offer,
      transferId: _activeTransferId!,
      files: sources.map((e) => e.entry).toList(),
      bytesTotal: _bytesTotal,
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
    // Serialize chunk writes — parallel unawaited handlers race the RAF.
    _chunkQueue = _chunkQueue.then((_) => _handleChunk(chunk));
  }

  Future<void> _handleControl(FileXferControl control) async {
    switch (control.op) {
      case FileXferOp.offer:
        await _onOffer(control);
        break;
      case FileXferOp.accept:
        if (control.transferId != _activeTransferId) return;
        _fileIndex = control.fileIndex;
        _bytesTransferred = _prefixBytes(
          _outgoing.map((e) => e.entry).toList(),
          control.fileIndex,
          control.resumeOffset,
        );
        _state = FileTransferState.transferring;
        _emitProgress();
        unawaited(_runSendLoop(
          startFileIndex: control.fileIndex,
          startOffset: control.resumeOffset,
        ));
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
        final checkpoint = await _resumeStore.lookup(control.transferId) ??
            await _resumeStore.findCompatible(control.files);
        await sendText(FileXferJsonCodec.encodeControl(FileXferControl(
          op: FileXferOp.resumeAck,
          transferId: control.transferId,
          files: control.files,
          fileIndex: checkpoint?.fileIndex ?? 0,
          resumeOffset: checkpoint?.resumeOffset ?? 0,
          bytesTotal: control.bytesTotal,
        )));
        break;
      case FileXferOp.resumeAck:
        break;
      default:
        break;
    }
  }

  Future<void> _onOffer(FileXferControl offer) async {
    var accept = autoAcceptIncoming;
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

    await Directory(receiveRoot).create(recursive: true);
    await _writer.close();
    _writer = FileReceiveWriter(receiveRoot);

    _isIncoming = true;
    _activeTransferId = offer.transferId;
    _activeCrc = FileChunkCodec.transferIdCrc32(offer.transferId);
    _incoming = offer.files;
    _outgoing = [];
    _bytesTotal = offer.files.fold<int>(0, (s, e) => s + e.size);
    _abortRequested = false;

    final checkpoint = await _resumeStore.lookup(offer.transferId) ??
        await _resumeStore.findCompatible(offer.files);
    var fileIndex = checkpoint?.fileIndex ?? 0;
    var offset = checkpoint?.resumeOffset ?? 0;

    if (fileIndex < offer.files.length) {
      await _writer.openFile(offer.files[fileIndex].relativePath,
          startOffset: offset);
      // On-disk length is authoritative after open (append resume).
      offset = _writer.expectedOffset;
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
    )));
  }

  Future<void> _handleChunk(FileChunk chunk) async {
    if (_activeCrc == null || chunk.transferIdCrc32 != _activeCrc) return;
    if (_state != FileTransferState.transferring || !_isIncoming) return;
    if (_abortRequested) return;
    if (chunk.fileIndex >= _incoming.length) return;

    try {
      final expectedRel =
          FileReceiveWriter.sanitizeRelative(_incoming[chunk.fileIndex].relativePath);
      if (_writer.openRelPath == null ||
          chunk.fileIndex != _fileIndex ||
          _writer.openRelPath != expectedRel) {
        _fileIndex = chunk.fileIndex;
        await _writer.openFile(_incoming[chunk.fileIndex].relativePath,
            startOffset: chunk.offset);
      }

      await _writer.writeChunk(chunk.offset, chunk.payload);
      _bytesTransferred += chunk.payload.length;
      _emitProgress();

      await _resumeStore.saveProgress(
        transferId: _activeTransferId!,
        files: _incoming,
        fileIndex: chunk.fileIndex,
        resumeOffset: _writer.expectedOffset,
      );

      // Window ACK (one progress per chunk keeps sender from flooding).
      await sendText(FileXferJsonCodec.encodeControl(FileXferControl(
        op: FileXferOp.progress,
        transferId: _activeTransferId!,
        fileIndex: chunk.fileIndex,
        resumeOffset: _writer.expectedOffset,
        bytesTransferred: _bytesTransferred,
        bytesTotal: _bytesTotal,
      )));

      final entry = _incoming[chunk.fileIndex];
      if (_writer.expectedOffset >= entry.size) {
        await _writer.close();
        final next = chunk.fileIndex + 1;
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
        final file = File(source.absolutePath);
        final raf = await file.open(mode: FileMode.read);
        try {
          var offset = (i == startFileIndex) ? startOffset : 0;
          if (offset > 0) {
            await raf.setPosition(offset);
          }
          while (offset < source.entry.size) {
            if (_abortRequested) return;
            while (_inFlight >= maxInFlight) {
              _windowSlot = Completer<void>();
              await _windowSlot!.future;
              if (_abortRequested) return;
            }
            final toRead =
                min(chunkSize, source.entry.size - offset);
            final payload = Uint8List(toRead);
            final read = await raf.readInto(payload);
            if (read <= 0) break;
            final slice =
                read == toRead ? payload : Uint8List.sublistView(payload, 0, read);
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
        } finally {
          await raf.close();
        }
      }
      // Wait for remaining ACKs / peer complete; peer sends complete.
      // If peer already completed, state may already be completed.
      if (!_abortRequested && _state == FileTransferState.transferring) {
        // Soft wait: progress ACKs continue; complete message finishes.
      }
    } catch (e) {
      _state = FileTransferState.failed;
      _emitProgress(error: e.toString());
      await abort(reason: e.toString());
    }
  }

  void _emitProgress({String? error}) {
    if (_progressController.isClosed) return;
    final files = _isIncoming ? _incoming : _outgoing.map((e) => e.entry).toList();
    _progressController.add(FileTransferProgress(
      transferId: _activeTransferId ?? '',
      state: error != null && _state != FileTransferState.aborted
          ? FileTransferState.failed
          : _state,
      bytesTransferred: _bytesTransferred,
      bytesTotal: _bytesTotal,
      fileIndex: _fileIndex,
      fileCount: files.length,
      currentPath:
          files.isEmpty ? null : files[min(_fileIndex, files.length - 1)].relativePath,
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
