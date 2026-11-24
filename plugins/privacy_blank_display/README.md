# privacy_blank_display

CloudPlayPlus Plus host plugin for **privacy / blank display** (防窥).

## Modes (UU-style ladder — ideas only, no NetEase code)

| Mode | Behavior |
|------|----------|
| `off` | No privacy surface |
| `blankDisplay` | Power off physical monitors (`SC_MONITORPOWER`). Stronger UU “关闭显示屏 via virtual screen” can reuse CPP `VDISPLAY_OCCUPY` + Parsec VDD. |
| `privacyScreen` | Topmost black overlays with `WDA_EXCLUDEFROMCAPTURE` so DXGI capture still sees the real desktop |

## Host hotkey

`Ctrl+Alt+P` dismisses the active privacy mode. Optional `LockWorkStation` after dismiss (default on).

## Platform

Windows host only for native blank/overlay. Other platforms: `isSupported() == false`.

## Constraints

- Do not copy NetEase binaries or decompiled bodies.
- Custom screensaver images: API reserved (`imagePath`); v1 uses solid black.
