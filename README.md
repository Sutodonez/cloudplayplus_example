# cloudplayplus_plus (cppp)

CloudPlayPlus Plus — enhancement fork of [CloudPlayPlus](https://www.cloudplayplus.com) with untouched upstream CPP tracked as a git submodule.

## Layout

| Path | Role |
|------|------|
| `vendor/cloudplayplus` | Vanilla CPP pin ([cloudplayplus_stone](https://github.com/zhuhaichao518/cloudplayplus_stone)) |
| `plugins/` | cppp-owned plugins only |
| `patches/` | Replayable diffs applied onto the pin |
| `docs/` | Layout, handoff, GameViewer REA reservation |
| `scripts/` | Init, bump, apply-patches, build |

Details: [docs/layout.md](docs/layout.md).

## Clone

```bash
git clone --recurse-submodules https://github.com/Sutodonez/cloudplayplus_plus.git
cd cloudplayplus_plus
# or:
scripts/submodule-init.sh
```

## Build

Primary build/dev target is the submodule (path deps into `vendor/` preferred over a full-tree overlay):

```bash
scripts/build.sh linux     # or windows|macos|web|apk|ios
# equivalent:
cd vendor/cloudplayplus && flutter pub get && flutter run
```

Bump upstream later with `scripts/bump-upstream.sh` (optional SHA), then replay `patches/`.

## Constraints

- Do not copy NetEase (网易) binaries or decompiled bodies.
- Keep CPP changes replayable onto future pins.
- `docs/reference/gameviewer/` is reserved for REA notes; bulky dumps go under `artifacts/`.
