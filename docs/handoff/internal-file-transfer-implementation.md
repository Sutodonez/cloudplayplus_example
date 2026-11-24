---
cursor:
  subagentId: "bc-7eae223a-7dba-5a5e-beff-dc6c0413c757"
---

# File transfer implementation notes

## Deliverable

- Branch: `cursor/feat-file-transfer-c757`
- Package: `plugins/session_file_transfer` (pure Dart, no native)
- App hooks: `lib/entities/session.dart`, `lib/entities/messages.dart` (`LP_FILE_CHUNK = 67`), floating menu → `lib/utils/widgets/file_transfer_sheet.dart`
- Deps: `session_file_transfer` path + `file_picker`

## Protocol

- Control JSON: `{"file_xfer": {op, transferId, files[], …}}`
- Binary chunks: opcode 67 + crc32(id) + fileIndex + offset + payload (16 KiB default)
- Folders flattened to relative paths; receive root `Downloads/CloudPlayPlusTransfers`

## Verification (FACT)

- `dart test` in `plugins/session_file_transfer`: codec round-trip, path sanitize, loopback file+folder, resume from partial ledger — **7 passed** (Dart 3.5.4)
- Full Flutter app / real WebRTC session: **not run** (no Flutter SDK in this environment)

## Gaps

| Item | Status |
|------|--------|
| Mid-transfer / re-offer resume | Implemented (ledger + append) |
| GV 断点续传 parity | **UNKNOWN** — marketing conflict; our resume is best-effort, not attested against UU |
| Web | Unsupported (`dart:io`) |
| Large-file sha256 | Only ≤ 4 MiB hashed by default |
| Host→controller send UI | Same sheet on controller session; host auto-accepts incoming |
| Hole punch / vhid | Out of scope (other workers) |
