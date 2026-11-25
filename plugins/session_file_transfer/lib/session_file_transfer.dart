/// Isolated session file/folder transfer for CloudPlayPlus.
///
/// Wire [FileTransferEngine] to a reliable RTC data channel (or any
/// ordered byte/text side channel). Control uses JSON envelopes; file
/// bytes use binary chunks with [kFileChunkOpcode].
///
/// Web controllers can send via [FileTransferEngine.sendNamedBytes]
/// (memory-backed). Desktop hosts receive with dart:io.
library session_file_transfer;

export 'src/protocol.dart';
export 'src/codec.dart';
export 'src/hashing.dart';
export 'src/local_source.dart';
export 'src/file_manifest.dart';
export 'src/file_io.dart'
    show
        defaultReceiveRoot,
        FileReceiveWriter,
        PathFileSource,
        buildManifestFromPaths,
        buildManifestFromNamedBytes;
export 'src/transfer_engine.dart';
export 'src/resume_store.dart';
