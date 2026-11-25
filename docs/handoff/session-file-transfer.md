# Session file/folder transfer

**Status:** open for review — [#2](https://github.com/Sutodonez/cloudplayplus_plus/pull/2)  
**Opcode:** `LP_FILE_CHUNK = 67`  
**Layout:** cppp plugin + replayable vendor patch (thinned `main`)

## Layers

| Path | Role |
|------|------|
| `plugins/session_file_transfer/` | Pure-Dart transfer engine (control JSON + binary chunks, folder flatten, UU-like resume) |
| `patches/0001-session-file-transfer.patch` | Wireup onto `vendor/cloudplayplus` |
| `patches/file-transfer/FILE_LIST.md` | Replay conflict surface |

## Behavior

- Control: JSON `file_xfer` envelopes (offer / accept / reject / abort / progress / complete / resume_* / resume_restart)
- Payload: binary opcode `LP_FILE_CHUNK` (67)
- Integrity: streaming sha256 for every file (no ≤4 MiB cap); full-file verify on receive complete
- Resume: ledger + chunk-aligned offsets + prefix sha256 verified by sender; content fingerprint
- Host: settings for **auto-accept** and **save path** (default `Downloads/CloudPlayPlusTransfers`)
- Controller: floating-menu folder icon → send sheet; **Web controller** sends via memory-backed pick
- Asymmetric progress UI (sender sheet; receiver MessageBox) — accepted for v1

## Opcode coordination

| Opcode | Constant | Owner |
|--------|----------|-------|
| 67 | `LP_FILE_CHUNK` | this PR |
| 68 | `LP_PRIVACY_MODE` | privacy (#9) — reserved in patch |
| 69 | `LP_TERM_CHUNK` | terminal (#8) — reserved in patch |

## Toolbar order

With #9 / #8: **privacy → file → terminal** (before close).

## Replay

```bash
scripts/submodule-init.sh
scripts/apply-patches.sh
cd vendor/cloudplayplus && flutter pub get
```
