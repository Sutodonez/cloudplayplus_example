# Privacy / blank display (防窥)

**Branch:** `cursor/privacy-blank-display-11c0`  
**Layout:** cppp plugin + replayable vendor patch (Phase 2 thinned `main`)

## What shipped

| Layer | Content |
|-------|---------|
| Plugin | `plugins/privacy_blank_display` (Windows): `off` / `blankDisplay` (monitor power-off + host mute) / `privacyScreen` (black overlay + `WDA_EXCLUDEFROMCAPTURE`); rebindable dismiss hotkey (default Ctrl+Alt+P); optional `LockWorkStation` |
| Patch | `patches/0002-privacy-blank-display-wireup.patch` — see `patches/privacy-blank/FILE_LIST.md` |
| Host GUI | Settings →「防窥」(non-Windows: grayed out, not hidden) |
| Controller GUI | Connect picker: 跟随被控默认 / 本次不启用 / 关闭屏幕背光 / 隐私屏保; in-session floating `visibility_off` temp override |
| Opcode | `LP_PRIVACY_MODE = 68` `[opcode, mode]` |

## Pre-merge landings (Human Q21–Q24)

| Item | Status |
|------|--------|
| Host mute while privacy on | Done (default render endpoint mute/restore) |
| Rebindable hotkey | Done (settings capture dialog; persisted) |
| `blankDisplay` ↔ `VDISPLAY_OCCUPY` auto-bind | Done at session start (`ensureExclusiveForBlankDisplay`) |
| Copy: 关闭屏幕背光 / 彻底关闭需独占 / 屏保留自定义图空间 | Done (settings + connect picker) |
| Non-Windows: gray out, don't hide | Done |
| Q22: host default; controller temp override | Done (`controllerPrivacyOverride`; null = follow host) |
| Host gate: allow controller override | Done (`privacyAllowControllerOverride`, default on) |
| Host gate: blankDisplay→VDISPLAY auto-bind | Done (`privacyAutoBindExclusive`, default on) |

## Review hardenings (PR #9 follow-up)

- Overlay/`setMode` failure rolls back mute+hotkey (no Dart/`_active` diverge)
- Floating toggle: follow-host (`-1`) treated as engaged → first tap forces off
- WDA affinity failure destroys overlay window (fail closed)
- Mute crash marker restore on plugin load; `lockWorkstation` requires `{confirm: true}`; `imagePath` rejected until whitelist loader
- Hotkey persist/native validation aligned with UI (letter/digit/F + required modifiers; dirty prefs sanitized)

## Deferred

- Custom screensaver **image** (`imagePath` reserved; solid black for now)
- macOS / Linux host native privacy
- Low: multi-session global singleton state

## Design sources (ideas only)

- `docs/reference/gameviewer/12-public-features.md` §7 — off / 关闭显示屏 / 隐私屏保; hotkey; lock; mute
- `docs/reference/gameviewer/99-vs-cloudplayplus.md` — host plugin + VDD blank path
- `docs/reference/gameviewer/02-architecture-map.md` / `04-oss-combination-points.md` — GV IDD vs OSS IddCx/VDD (do **not** copy NetEase drivers)

## Verify

```bash
scripts/submodule-init.sh
scripts/apply-patches.sh
cd vendor/cloudplayplus && flutter pub get
# Windows host: privacy screen / blank display; rebind hotkey; mute; exclusive auto-bind
```
