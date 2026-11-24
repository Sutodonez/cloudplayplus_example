# Replay surface — session file transfer

Paths inside `vendor/cloudplayplus` touched by `patches/0001-session-file-transfer.patch`:

| Path | Change |
|------|--------|
| `pubspec.yaml` | Path-dep `session_file_transfer` → `../../plugins/session_file_transfer`; add `file_picker` |
| `lib/entities/messages.dart` | `LP_FILE_CHUNK=67` (owned); reserve `LP_PRIVACY_MODE=68`, `LP_TERM_CHUNK=69` |
| `lib/entities/session.dart` | `FileTransferEngine` wiring on reliable data channel |
| `lib/utils/widgets/device_tile_page.dart` | Floating-menu folder entry |
| `lib/utils/widgets/file_transfer_sheet.dart` | Controller GUI (new) |

cppp-owned (not in the patch; live at repo root):

- `plugins/session_file_transfer/**`

## Merge notes

Floating-menu index 5 / `Icons.folder_open` conflicts with sibling terminal (#8) and privacy (#9) if they also insert before `Icons.close`. Reconcile icon order when stacking feature PRs.
