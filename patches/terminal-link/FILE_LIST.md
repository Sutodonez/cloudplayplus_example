# Replay surface — session terminal link

Paths inside `vendor/cloudplayplus` touched by `patches/0003-session-terminal-link.patch`
(applies after ambient `0001` + privacy `0002`):

| Path | Change |
|------|--------|
| `pubspec.yaml` | Path-dep `session_terminal_link` → `../../plugins/session_terminal_link` |
| `lib/entities/messages.dart` | `LP_FILE_CHUNK=67` (reserved), keep `LP_PRIVACY_MODE=68`, add `LP_TERM_CHUNK=69` |
| `lib/entities/session.dart` | `TerminalLinkEngine` wiring on reliable data channel (alongside privacy opcode handler) |
| `lib/utils/widgets/device_tile_page.dart` | Floating-menu terminal entry after privacy; Q2 order privacy → file → terminal → close |
| `lib/utils/widgets/terminal_link_sheet.dart` | Chinese controller GUI + 分屏 / 本机终端附着 |

cppp-owned (not in the patch; live at repo root):

- `plugins/session_terminal_link/**` — ConPTY FFI, psmux CLI, WT visible attach, engine, tests
