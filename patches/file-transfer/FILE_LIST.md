# Replay surface — session file transfer

Paths inside `vendor/cloudplayplus` touched by `patches/0004-session-file-transfer.patch`
(applies after ambient `0001` + privacy `0002` + terminal `0003`):

| Path | Change |
|------|--------|
| `pubspec.yaml` | Path-dep `session_file_transfer` + `file_picker` |
| `lib/entities/session.dart` | `FileTransferEngine` wiring alongside privacy + terminal handlers |
| `lib/utils/widgets/device_tile_page.dart` | Floating-menu `folder_open` (Q2: privacy → file → terminal → close) |
| `lib/utils/widgets/file_transfer_sheet.dart` | Controller GUI |
| `lib/utils/widgets/file_transfer_settings_screen.dart` | Auto-accept + save directory |
| `lib/utils/widgets/message_box.dart` | `showConfirm` for manual accept |
| `lib/settings_screen.dart` | Navigation tile → file transfer settings |

Opcode `LP_FILE_CHUNK=67` is introduced earlier by terminal patch as a reserved constant; this feature owns the wire protocol.

cppp-owned (not in the patch; live at repo root):

- `plugins/session_file_transfer/**`
