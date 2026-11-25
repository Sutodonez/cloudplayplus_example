/// Isolated remote terminal linking for CloudPlayPlus Plus (cppp).
///
/// Wire [TerminalLinkEngine] to a reliable RTC data channel. Control uses
/// JSON envelopes; stdout/stderr bytes use binary chunks with
/// [kTermChunkOpcode].
///
/// Windows host prefers **psmux + ConPTY**; falls back to bare ConPTY then
/// pipes. Supports psmux multi-pane and Windows Terminal visible attach.
library session_terminal_link;

export 'src/protocol.dart';
export 'src/codec.dart';
export 'src/host_shell.dart';
export 'src/terminal_engine.dart';
export 'src/backends/shell_backend.dart';
export 'src/backends/psmux.dart';
export 'src/backends/visible_attach_win.dart';
export 'src/backends/backend_factory.dart';
