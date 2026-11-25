# Replay surface — post-merge security hardening

Paths inside `vendor/cloudplayplus` touched by
`patches/0007-post-merge-security-hardening.patch` (applies after `0001`…`0006`):

| Path | Change |
|------|--------|
| `lib/services/reliable_channel_gate.dart` | **New** — priority + bufferedAmount backpressure gate |
| `lib/services/privacy_session_modes.dart` | **New** — per-session strongest-wins aggregator |
| `lib/services/privacy_blank_service.dart` | Per-session modes; SendInput hold under blank/exclusive |
| `lib/services/streamed_manager.dart` | `onSessionStarted/Ended` with session id + exclusive flag |
| `lib/entities/session.dart` | Channel gate wireup; auto-accept default false; privacy session id |
| `lib/utils/widgets/streaming_floating_menu.dart` | **New** — named floating-menu actions |
| `lib/utils/widgets/device_tile_page.dart` | Use enum instead of bare indices |
| `lib/utils/widgets/file_transfer_settings_screen.dart` | Default auto-accept false + trust copy |
| `plugins/hardware_simulator/windows/mouse_injector.{h,cpp}` | Exclusive/blank mapping comments |
| `plugins/hardware_simulator/windows/hardware_simulator_plugin.cpp` | SendInput fallback comments |
| `test/reliable_channel_gate_test.dart` | **New** |
| `test/privacy_session_modes_test.dart` | **New** |
| `test/streaming_floating_menu_test.dart` | **New** |

cppp-owned (not in the patch; live at repo root):

- `plugins/session_file_transfer/**` — engine default `autoAcceptIncoming: false`
- `docs/handoff/post-merge-security-hardening.md`
