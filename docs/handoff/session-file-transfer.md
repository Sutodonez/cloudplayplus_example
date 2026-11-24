# Session file/folder transfer

**Status:** open for review — [#2](https://github.com/Sutodonez/cloudplayplus_plus/pull/2)  
**Opcode:** `LP_FILE_CHUNK = 67`  
**Layout:** cppp plugin + replayable vendor patch (thinned `main`)

## Layers

| Path | Role |
|------|------|
| `plugins/session_file_transfer/` | Pure-Dart transfer engine (control JSON + binary chunks, folder flatten, best-effort resume) |
| `patches/0001-session-file-transfer.patch` | Wireup onto `vendor/cloudplayplus` |
| `patches/file-transfer/FILE_LIST.md` | Replay conflict surface |

## Behavior

- Control: JSON `file_xfer` envelopes (offer / accept / reject / abort / progress / complete / resume_*)
- Payload: binary opcode `LP_FILE_CHUNK` (67)
- Host auto-accepts into `Downloads/CloudPlayPlusTransfers`
- Controller: floating-menu folder icon → send files/folder sheet

## Opcode coordination

| Opcode | Constant | Owner |
|--------|----------|-------|
| 67 | `LP_FILE_CHUNK` | this PR |
| 68 | `LP_PRIVACY_MODE` | privacy (#9) — reserved in patch |
| 69 | `LP_TERM_CHUNK` | terminal (#8) — reserved in patch |

## Gaps

- GV/UU 断点续传 product parity: **UNKNOWN**
- Web unsupported (`dart:io`)
- Large-file content hash only for files ≤ 4 MiB by default
- Floating-menu index conflicts with sibling feature PRs until icon order is reconciled

## Replay

```bash
scripts/submodule-init.sh
scripts/apply-patches.sh
cd vendor/cloudplayplus && flutter pub get
```
