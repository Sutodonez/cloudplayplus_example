# cloudplayplus_plus (cppp)

CloudPlayPlus Plus — enhancement fork of [CloudPlayPlus](https://www.cloudplayplus.com) with untouched upstream CPP tracked as a git submodule.

## Layout (worker index)

| Path | Role |
|------|------|
| `vendor/cloudplayplus` | Vanilla CPP pin ([cloudplayplus_stone](https://github.com/zhuhaichao518/cloudplayplus_stone)) |
| `plugins/` | cppp-owned plugins only |
| `patches/` | Replayable diffs applied onto the pin |
| `docs/layout.md` | Full layout rules |
| `docs/handoff/` | Portable enhancement handoff docs |
| [`docs/reference/gameviewer/`](docs/reference/gameviewer/) | **GameViewer / UU远程 RE pack** — notes + curated dumps (start at [README](docs/reference/gameviewer/README.md)) |
| `docs/reference/gameviewer/artifacts/` | Curated RE text dumps (not NetEase binaries) |
| `artifacts/` | Local scratch dumps only (gitignored) |
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

- Do not copy NetEase (网易) binaries or decompiled bodies into product / plugin / vendor code.
- Keep CPP changes replayable onto future pins.
- Cross-agent GameViewer RE exchange path: `docs/reference/gameviewer/` (notes) + `docs/reference/gameviewer/artifacts/` (dumps). Do not confuse with root `artifacts/` (local scratch).
