# session_file_transfer

Isolated Dart module for CloudPlayPlus **session file/folder transfer** (cppp plugin).

## Design

- **Transport:** reliable WebRTC data channel (or any ordered side channel).
- **Control:** JSON envelope `{"file_xfer": {...}}` (offer / accept / reject /
  abort / progress / complete / resume_query / resume_ack).
- **Payload:** binary chunks with opcode `67` (`kFileChunkOpcode` /
  `LP_FILE_CHUNK`).
- **Folders:** flattened to relative paths under the selected root folder name.
- **Resume:** best-effort via local ledger (`.cpp_file_xfer_resume.json`) +
  append writes. Peer re-offer with same id or matching size/sha256 continues
  from on-disk length.

## Layout (thinned cppp)

| Path | Role |
|------|------|
| `plugins/session_file_transfer/` | This package (cppp-owned) |
| `patches/0001-session-file-transfer.patch` | Vendor wireup onto `vendor/cloudplayplus` |
| `patches/file-transfer/FILE_LIST.md` | Replay conflict surface |

```bash
scripts/submodule-init.sh
scripts/apply-patches.sh
cd vendor/cloudplayplus && flutter pub get
```

Wireup: path-dep in vendor `pubspec.yaml`, `FileTransferEngine` in `session.dart`,
floating-menu folder icon → `file_transfer_sheet.dart`.

## Gaps

| Topic | Status |
|-------|--------|
| Mid-session abort → re-offer resume | Implemented (ledger + append) |
| Cross-disconnect resume | Partial — requires peer to re-offer; identity is size/path/(optional sha), not cryptographically bound to the remote user |
| Web (`dart:io`) | Not supported |
| Integrity for large files | sha256 only for files ≤ 4 MiB by default |
| GV/UU “断点续传” marketing parity | **UNKNOWN**; this module implements a minimal resume, not a verified clone |
