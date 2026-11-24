# Repository layout (cppp over CPP)

This repository is **cloudplayplus_plus** (**cppp**): the primary development surface for CloudPlayPlus Plus enhancements. Untouched upstream CloudPlayPlus (**CPP**) lives only under `vendor/cloudplayplus`.

## Layers

| Path | Role |
|------|------|
| `vendor/cloudplayplus` | Git submodule — vanilla CPP pin (build/run target) |
| `plugins/` | **cppp-owned** plugins only (not a copy of upstream plugins) |
| `patches/` | Replayable patch series applied onto the vendor pin |
| `docs/handoff/` | Portable enhancement handoff docs |
| `docs/reference/gameviewer/` | Reserved for GameViewer REA notes (no NetEase binaries) |
| `artifacts/` | Local bulky dumps (gitignored contents) |
| `scripts/` | Submodule init, upstream bump, patch apply, build helpers |
| `overlay/` | Optional; prefer path deps into `vendor/` instead of a full-tree overlay |

**Upstream submodule URL:** https://github.com/zhuhaichao518/cloudplayplus_stone  
**Pin SHA:** `87c0920ad80e2f57ffbbb12545d633058d851c4c`

## Clone

```bash
git clone --recurse-submodules https://github.com/Sutodonez/cloudplayplus_plus.git
cd cloudplayplus_plus
# or after a plain clone:
scripts/submodule-init.sh
```

## Build / develop

Primary app tree is the submodule:

```bash
scripts/apply-patches.sh          # no-op until patches exist
scripts/build.sh linux            # runs flutter build inside vendor/cloudplayplus
# equivalent:
cd vendor/cloudplayplus && flutter pub get && flutter run -d windows
```

Upstream plugins already live under `vendor/cloudplayplus/plugins/` (via the pin). Do **not** re-vend them at the cppp root.

## Path dependencies (preferred over overlay)

When a cppp plugin needs a CPP package, depend on it by path into the submodule:

```yaml
# plugins/<cppp_plugin>/pubspec.yaml
dependencies:
  flutter_webrtc:
    path: ../../vendor/cloudplayplus/plugins/flutter-webrtc
```

To register that plugin with the CPP app, add a replayable patch under `patches/` that edits `vendor/cloudplayplus/pubspec.yaml` (and call sites) — do not copy the vendor tree into `overlay/` unless a path-dep approach is proven insufficient.

## Scripts

| Script | Purpose |
|--------|---------|
| `scripts/submodule-init.sh` | Init/sync submodules; check out recorded pin |
| `scripts/bump-upstream.sh [sha]` | Bump CPP pin to `origin/main` or an explicit SHA |
| `scripts/apply-patches.sh` | Apply `patches/*.patch` onto `vendor/cloudplayplus` (ordered) |
| `scripts/build.sh <target>` | `flutter pub get` + build inside the vendor pin |

## Phases

1. **Phase 1:** Submodule + init/bump scripts + layout doc (root Flutter tree still present).
2. **Phase 2 (current):** Root thinned to cppp-only; build against `vendor/cloudplayplus`; duplicate vanilla sources removed from root.

## Rules of thumb

- Do not commit ad-hoc edits inside `vendor/` without regenerating patches.
- Do not copy NetEase (网易) binaries into this tree.
- Hole punching remains the highest-priority enhancement track; changes must stay replayable onto future upstream pins.
- Open feature PRs (#1–#3/#4) still target the pre-thin history; rebase/retarget them onto this layout separately.
