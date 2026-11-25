# session_file_transfer

Isolated Dart module for CloudPlayPlus **session file/folder transfer** (cppp plugin).

## Design

- **Transport:** reliable WebRTC data channel (or any ordered side channel).
- **Control:** JSON envelope `{"file_xfer": {...}}` (offer / accept / reject /
  abort / progress / complete / resume_query / resume_ack / resume_restart).
- **Payload:** binary chunks with opcode `67` (`kFileChunkOpcode` /
  `LP_FILE_CHUNK`).
- **Folders:** flattened to relative paths under the selected root folder name.
- **Integrity:** streaming sha256 for every offered file (no ≤4 MiB cap);
  receiver verifies full-file hash on complete.
- **Resume (UU-like):** local ledger + chunk-aligned offsets + prefix sha256
  verified by the sender before continuing; content fingerprint for
  cross-offer identity; `resume_restart` on mismatch.
- **Web controller:** `sendNamedBytes` / in-memory sources (no `dart:io` on
  the send path). Host receive still needs desktop `dart:io`.

## Layout (thinned cppp)

| Path | Role |
|------|------|
| `plugins/session_file_transfer/` | This package (cppp-owned) |
| `patches/0004-session-file-transfer.patch` | Vendor wireup onto `vendor/cloudplayplus` |
| `patches/file-transfer/FILE_LIST.md` | Replay conflict surface |

```bash
scripts/submodule-init.sh
scripts/apply-patches.sh
cd vendor/cloudplayplus && flutter pub get
```

Wireup: path-dep in vendor `pubspec.yaml`, `FileTransferEngine` in `session.dart`,
floating-menu folder icon → `file_transfer_sheet.dart`, settings for auto-accept
and save path. Floating toolbar order (with #9/#8): **privacy → file → terminal**.

## Gaps

| Topic | Status |
|-------|--------|
| Mid-session abort → re-offer resume | Implemented (ledger + prefix verify + append) |
| Cross-disconnect resume | Strengthened — fingerprint + sha256 + prefix verify; still not cryptographically bound to the remote user |
| Web controller send | Supported via memory-backed sources |
| Web as receive host | Not supported (`dart:io` Downloads path) |
| Integrity for large files | Streaming sha256 for all sizes |
| GV/UU “断点续传” marketing clone | Not claimed; this is a stronger engineering resume, not a verified UU binary clone |
