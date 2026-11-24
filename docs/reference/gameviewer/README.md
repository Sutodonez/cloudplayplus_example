# GameViewer / 网易UU远程 — design reference

**Product:** GameViewer 远程 → **网易UU远程** (`uuyc.163.com`)  
**Analyzed build:** `4.48.1.5606` (Windows host-side RE)  
**Purpose:** Capability and design reference for CloudPlayPlus Plus (cppp) planning.

This tree is a sibling of [`docs/handoff/`](../../handoff/) when that handoff set is present on a branch. See also [`docs/layout.md`](../../layout.md).

## Hard constraints

1. **Reference only** for capability / architecture / design decisions.
2. **Forbidden:** copying NetEase binaries (`.exe` / `.dll` / installers / drivers from GameViewer `Input/`) into this repository or into product code.
3. **Forbidden:** pasting or porting **decompiled function bodies** from `artifacts/*.c` (or equivalent dumps) into product / plugin / vendor code. Use these dumps only to understand behavior; re-implement cleanly from public APIs and your own design.
4. Artifacts here are Ghidra/CLI text dumps, curated strings, JSON Evidence, and helper scripts — not redistributable product binaries.

## Readable notes (index)

| File | Content |
|------|---------|
| [01-inventory.md](./01-inventory.md) | Binaries / modules / drivers / roles |
| [02-architecture-map.md](./02-architecture-map.md) | Feature structure (NAT, mouse, terminal + others) |
| [03-implementation-routes.md](./03-implementation-routes.md) | Protocols, call paths, evidence paths |
| [04-oss-combination-points.md](./04-oss-combination-points.md) | Later OSS match candidates |
| [05-deep-pass-nat-ice.md](./05-deep-pass-nat-ice.md) | `streamer.dll` ICE / punch / relay (strings) |
| [06-deep-pass-mouse.md](./06-deep-pass-mouse.md) | Server mouse / VHID / ViGEm deep pass |
| [07-deep-pass-terminal.md](./07-deep-pass-terminal.md) | Terminal + `conpty_bridge` argv/IPC |
| [08-deep-pass-nat-ghidra.md](./08-deep-pass-nat-ghidra.md) | `streamer.dll` Ghidra decompile evidence |
| [09-deep-pass-server-ghidra.md](./09-deep-pass-server-ghidra.md) | Server mouse/terminal Ghidra evidence |
| [10-analysis-summary.md](./10-analysis-summary.md) | Concise RE verdict (NAT / mouse / terminal) |
| [11-tech-notes-plain.md](./11-tech-notes-plain.md) | Plain-language design notes (选型) |
| [12-public-features.md](./12-public-features.md) | Official / community public feature appendix |
| [99-vs-cloudplayplus.md](./99-vs-cloudplayplus.md) | CPP vs GV comparison & migration ranking |

## Artifacts

Large dumps live under [`artifacts/`](./artifacts/) (JSON CLI captures, curated `.txt`, decompiled site `.c`, helper `.js`).

| Metric | Value (this publish) |
|--------|----------------------|
| Artifact file count | 135 (empty `.err` / empty JSON omitted) |
| Largest file | `cli-server-fn-pathcaller-70d56b.json` ≈ **2.83 MiB** |
| Files ≥ 1 MiB | 6 JSON dumps (pathcaller / punch / ICE sites) |
| Tree total (notes + artifacts) | ≈ **18.4 MiB** |

**git-lfs:** not enabled for this publish — no individual file approaches GitHub’s soft (50 MiB) or hard (100 MiB) blob limits. If a future dump exceeds ~40 MiB, track it with git-lfs (or keep it out of git and link an external archive) and note the strategy here.

## Source provenance

- Primary RE outputs: local `GameViewer/Output/` analysis tree (not committed as Input/PEs).
- Readable narrative docs mirrored from the analysis Project store into `10`–`12` and `99`.
- Handoff branch may already carry overlapping narrative under `docs/handoff/`; this `reference/gameviewer/` tree is the canonical long-term home for RE notes + artifacts.
