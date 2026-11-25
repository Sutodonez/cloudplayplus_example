# privacy_blank_display

CloudPlayPlus Plus host plugin for **privacy / blank display** (防窥).

## Modes (UU-style ladder — ideas only, no NetEase code)

| Mode | Behavior |
|------|----------|
| `off` | No privacy surface |
| `blankDisplay` | Power off physical monitors (`SC_MONITORPOWER`). Dart wireup auto-binds exclusive virtual display (`VDISPLAY_OCCUPY` + Parsec VDD) at session start. |
| `privacyScreen` | Topmost black overlays with `WDA_EXCLUDEFROMCAPTURE` so DXGI capture still sees the real desktop |

While any non-off mode is active, the host default render audio endpoint is **muted** and restored when privacy turns off.

## Host hotkey

Rebindable dismiss hotkey (default `Ctrl+Alt+P`). Optional `LockWorkStation` after dismiss (default on). Configure via `PrivacyBlankDisplay.setHotkey` / host settings UI.

## Platform

Windows host only for native blank/overlay/mute. Other platforms: `isSupported() == false` (settings entry is grayed out, not hidden).

## Constraints

- Do not copy NetEase binaries or decompiled bodies.
- Custom screensaver images: API reserved (`imagePath`); v1 uses solid black and rejects path args on the method channel until a whitelist loader exists.
- `lockWorkstation` requires `{confirm: true}`; host mute crash recovery via temp marker file.
