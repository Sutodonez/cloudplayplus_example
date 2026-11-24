/// Isolated session file/folder transfer for CloudPlayPlus.
///
/// Wire [FileTransferEngine] to a reliable RTC data channel (or any
/// ordered byte/text side channel). Control uses JSON envelopes; file
/// bytes use binary chunks with [kFileChunkOpcode].
library session_file_transfer;

export 'src/protocol.dart';
export 'src/codec.dart';
export 'src/file_manifest.dart';
export 'src/transfer_engine.dart';
export 'src/resume_store.dart';
