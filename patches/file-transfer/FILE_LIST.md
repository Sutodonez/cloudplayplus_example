# Replay surface — session file transfer

Paths inside `vendor/cloudplayplus` touched by `patches/0001-session-file-transfer.patch`:

| Path | Change |
|------|--------|
| `pubspec.yaml` | Path-dep `session_file_transfer` → `../../plugins/session_file_transfer`; add `file_picker` |
| `lib/entities/messages.dart` | `LP_FILE_CHUNK=67` (owned); reserve `LP_PRIVACY_MODE=68`, `LP_TERM_CHUNK=69` |
| `lib/entities/session.dart` | `FileTransferEngine` wiring; prefs for auto-accept / save path; Web send via `sendFileBytes` |
| `lib/utils/widgets/device_tile_page.dart` | Floating-menu folder entry |
| `lib/utils/widgets/file_transfer_sheet.dart` | Controller GUI (desktop paths + Web memory pick) |
| `lib/utils/widgets/file_transfer_settings_screen.dart` | Auto-accept toggle + configurable save directory |
| `lib/utils/widgets/message_box.dart` | `showConfirm` for manual accept |
| `lib/settings_screen.dart` | Navigation tile → file transfer settings |

cppp-owned (not in the patch; live at repo root):

- `plugins/session_file_transfer/**`

## Merge notes

Floating-menu order when stacking with #9 / #8 (Human Q2): **privacy (`visibility_off`) → file (`folder_open`) → terminal → close**.

This patch alone inserts `folder_open` before `close`. Reconcile icon indices when applying privacy/terminal patches.
