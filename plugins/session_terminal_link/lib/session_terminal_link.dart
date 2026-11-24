/// Isolated remote terminal linking for CloudPlayPlus Plus (cppp).
///
/// Wire [TerminalLinkEngine] to a reliable RTC data channel. Control uses
/// JSON envelopes; stdout/stderr bytes use binary chunks with
/// [kTermChunkOpcode].
library session_terminal_link;

export 'src/protocol.dart';
export 'src/codec.dart';
export 'src/host_shell.dart';
export 'src/terminal_engine.dart';
