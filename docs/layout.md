# Repository layout (cppp over CPP)

This repository is **cloudplayplus_plus** (**cppp**): the primary development surface for CloudPlayPlus Plus enhancements. Untouched upstream CloudPlayPlus (**CPP**) is tracked as a git submodule.

## Layers

| Path | Role |
|------|------|
| `vendor/cloudplayplus` | Git submodule — vanilla CPP pin from upstream |
| Repo root (**cppp**) | Working Flutter app (legacy tree in Phase 1), plugins, patches, overlays, docs, scripts |

**Upstream submodule URL:** https://github.com/zhuhaichao518/cloudplayplus_stone  
**Initial pin SHA:** `87c0920ad80e2f57ffbbb12545d633058d851c4c` (`main` as of the Phase 1 scaffold)

## Clone

```bash
git clone --recurse-submodules https://github.com/Sutodonez/cloudplayplus_plus.git
cd cloudplayplus_plus
```

If you already cloned without submodules:

```bash
scripts/submodule-init.sh
# equivalent: git submodule update --init --recursive
```

## Scripts

| Script | Purpose |
|--------|---------|
| `scripts/submodule-init.sh` | Init/sync all submodules and check out the recorded `vendor/cloudplayplus` pin |
| `scripts/bump-upstream.sh [sha]` | Move the CPP pin to `origin/main` or an explicit SHA (stages the gitlink) |

## Phases

1. **Phase 1 (this scaffold):** Add `vendor/cloudplayplus` + scripts + this layout doc. The existing root Flutter tree stays in place so open feature PRs remain intact. Do **not** treat root sources as deleted or relocated yet.
2. **Phase 2 (later):** Thin the root to cppp-only (plugins / patches / overlay); build against the vendor pin; retire duplicate root sources.

## Rules of thumb

- Develop under the cppp root (and future `patches/` / `overlay/`). Do not commit ad-hoc edits inside `vendor/` without regenerating patches.
- Do not copy NetEase (网易) binaries into this tree.
- Hole punching remains the highest-priority enhancement track; changes must stay replayable onto future upstream pins.
