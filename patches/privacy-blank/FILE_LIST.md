# Privacy / blank display — owned vendor paths

Replayable patch: `patches/0001-privacy-blank-display-wireup.patch`  
Plugin (cppp root, not in patch): `plugins/privacy_blank_display/`

## FILE_LIST (conflict surface on upstream bump)

| Path | Role |
|------|------|
| `pubspec.yaml` | Path dep → `../../plugins/privacy_blank_display` |
| `lib/services/privacy_blank_service.dart` | Host orchestrator (mute/hotkey/VDD auto-bind/Q22 + policy gates) |
| `lib/services/app_init_service.dart` | Init privacy service on Windows |
| `lib/services/streamed_manager.dart` | Engage/restore; blankDisplay→VDISPLAY_OCCUPY (gated) |
| `lib/entities/messages.dart` | `LP_PRIVACY_MODE = 68` |
| `lib/entities/session.dart` | Opcode handler → `applyControllerMode` + `requestHostPrivacyMode` |
| `lib/global_settings/streaming_settings.dart` | Host defaults + override allow / exclusive auto-bind flags |
| `lib/settings_screen.dart` | Host「防窥」settings (policy toggles; hotkey; non-Win grayed) |
| `lib/utils/widgets/device_tile_page.dart` | Connect privacy picker + floating menu toggle (follow-host fix) |

## Replay

1. `scripts/submodule-init.sh`
2. `scripts/apply-patches.sh`
3. `cd vendor/cloudplayplus && flutter pub get`
4. Manual: Windows host — blank display (exclusive auto-bind) / privacy screen; rebind hotkey; mute; dismiss + lock

## Design anchors (reference only)

- Public UU modes: off / 关闭显示屏 / 隐私屏保 — `docs/reference/gameviewer/12-public-features.md`
- Plugin + VDD blank path — `docs/reference/gameviewer/99-vs-cloudplayplus.md`
- RE: IDD/virtual display is GV’s blank path; cppp uses Parsec VDD (existing) + overlay with `WDA_EXCLUDEFROMCAPTURE` — no NetEase IDD
