# Replay surface — session terminal link

Paths inside `vendor/cloudplayplus` touched by `patches/0001-session-terminal-link.patch`:

| Path | Change |
|------|--------|
| `pubspec.yaml` | Path-dep `session_terminal_link` → `../../plugins/session_terminal_link` |
| `lib/entities/messages.dart` | `LP_FILE_CHUNK=67` (reserved), `LP_PRIVACY_MODE=68` (reserved for privacy PR), `LP_TERM_CHUNK=69` |
| `lib/entities/session.dart` | `TerminalLinkEngine` wiring on reliable data channel |
| `lib/utils/widgets/device_tile_page.dart` | Floating-menu terminal entry |
| `lib/utils/widgets/terminal_link_sheet.dart` | Controller GUI (new) |

cppp-owned (not in the patch; live at repo root):

- `plugins/session_terminal_link/**`
