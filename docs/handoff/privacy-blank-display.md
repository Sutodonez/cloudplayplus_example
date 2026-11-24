# Privacy / blank display (防窥)

**Branch:** `cursor/privacy-blank-display-11c0`  
**Layout:** cppp plugin + replayable vendor patch (Phase 2 thinned `main`)

## What shipped

| Layer | Content |
|-------|---------|
| Plugin | `plugins/privacy_blank_display` (Windows): `off` / `blankDisplay` (monitor power-off) / `privacyScreen` (black overlay + `WDA_EXCLUDEFROMCAPTURE`); Ctrl+Alt+P dismiss; optional `LockWorkStation` |
| Patch | `patches/0001-privacy-blank-display-wireup.patch` — see `patches/privacy-blank/FILE_LIST.md` |
| Host GUI | Settings →「防窥 / Privacy blank display」 |
| Controller GUI | Device advanced: privacy radio; in-session floating menu `visibility_off` toggles privacy screen |
| Opcode | `LP_PRIVACY_MODE = 68` `[opcode, mode]` |

## Design sources (ideas only)

- `docs/reference/gameviewer/12-public-features.md` §7 — off / 关闭显示屏 / 隐私屏保; hotkey; lock
- `docs/reference/gameviewer/99-vs-cloudplayplus.md` — host plugin + VDD blank path
- `docs/reference/gameviewer/02-architecture-map.md` / `04-oss-combination-points.md` — GV IDD vs OSS IddCx/VDD (do **not** copy NetEase drivers)

## Gaps

- Custom screensaver **image** not implemented (solid black only; `imagePath` reserved)
- macOS / Linux host privacy not implemented (`isSupported == false`)
- UU “关闭显示屏 via virtual screen carrying desktop” is only partially matched: `blankDisplay` uses panel power-off; stronger blanking still available via existing **独占模式** (`VDISPLAY_OCCUPY` + Parsec VDD)
- Host mute-while-remote not in this PR
- Hotkey not user-remappable yet
- `privacyLockOnDisconnect` uses `LockWorkStation` (no Face ID / auto-unlock story)

## Verify

```bash
scripts/submodule-init.sh
scripts/apply-patches.sh
cd vendor/cloudplayplus && flutter pub get
# Windows host: connect with privacy screen / blank display; Ctrl+Alt+P
```
