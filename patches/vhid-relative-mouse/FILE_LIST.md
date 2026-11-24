# Owned files — VHID / relative mouse

**Upstream HS pin:** `vendor/cloudplayplus/plugins/hardware_simulator` @ `19dc81a`  
**Apply:** `scripts/apply-patches.sh` → `patches/0001-*.patch` + `patches/0002-*.patch`

## New (via `0001-vhid-relative-mouse-hs.patch`)

- `plugins/hardware_simulator/windows/mouse_injector.h`
- `plugins/hardware_simulator/windows/mouse_injector.cpp`
- `plugins/hardware_simulator/windows/vhid_mouse.h`
- `plugins/hardware_simulator/windows/vhid_mouse.cpp`

## Modified (HS — `0001`)

- `plugins/hardware_simulator/windows/CMakeLists.txt`
- `plugins/hardware_simulator/windows/hardware_simulator_plugin.cpp`
- `plugins/hardware_simulator/macos/Classes/HardwareSimulatorPlugin.swift`
- `plugins/hardware_simulator/lib/hardware_simulator.dart`
- `plugins/hardware_simulator/lib/hardware_simulator_method_channel.dart`
- `plugins/hardware_simulator/lib/hardware_simulator_platform_interface.dart`
- `plugins/hardware_simulator/test/hardware_simulator_method_channel_test.dart`
- `plugins/hardware_simulator/CHANGELOG.md`

## Modified (CPP app — `0002-vhid-relative-mouse-app-wireup.patch`)

- `lib/global_settings/streaming_settings.dart` — `useVhidMouse`
- `lib/services/app_init_service.dart` — apply backend on Windows host start
- `lib/settings_screen.dart` — host toggle under 键鼠设置

## Unchanged by design

- `lib/entities/messages.dart` (`LP_MOUSEMOVE_RELATIVE`)
- Relative move request/handle path in `hardware_input_controller.dart` / `session.dart`

## Not in this PR

- Full `hardware_simulator` tree absorb at cppp `plugins/` (pre-thin approach) — HS stays the nested vendor submodule.
- WinUHid driver / `WinUHid.dll` (host-installed; not bundled).
