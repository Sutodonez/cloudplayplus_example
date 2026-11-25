# Owned files — VHID mouse (relative + absolute)

**Upstream HS pin:** `vendor/cloudplayplus/plugins/hardware_simulator` @ `19dc81a`  
**Apply:** `scripts/apply-patches.sh` → `patches/0001-*.patch` + `patches/0002-*.patch`

## New (via `0005-vhid-relative-mouse-hs.patch`)

- `plugins/hardware_simulator/windows/mouse_injector.h`
- `plugins/hardware_simulator/windows/mouse_injector.cpp`
- `plugins/hardware_simulator/windows/vhid_mouse.h`
- `plugins/hardware_simulator/windows/vhid_mouse.cpp`

## Modified (HS — `0001`)

- `plugins/hardware_simulator/windows/CMakeLists.txt`
- `plugins/hardware_simulator/windows/hardware_simulator_plugin.cpp` — relative + absolute → injector
- `plugins/hardware_simulator/macos/Classes/HardwareSimulatorPlugin.swift`
- `plugins/hardware_simulator/lib/hardware_simulator.dart`
- `plugins/hardware_simulator/lib/hardware_simulator_method_channel.dart`
- `plugins/hardware_simulator/lib/hardware_simulator_platform_interface.dart`
- `plugins/hardware_simulator/test/hardware_simulator_method_channel_test.dart`
- `plugins/hardware_simulator/CHANGELOG.md`

## Modified (CPP app — `0006-vhid-relative-mouse-app-wireup.patch`)

- `lib/global_settings/streaming_settings.dart` — `useVhidMouse`
- `lib/services/app_init_service.dart` — apply backend on Windows host start
- `lib/settings_screen.dart` — title + description switch; **安装 WinUHid 驱动** button + guide

## Unchanged by design

- `lib/entities/messages.dart` (`LP_MOUSEMOVE_RELATIVE` / absolute framing)
- Relative / absolute move request/handle path in `hardware_input_controller.dart` / `session.dart`

## Not in this PR

- Full `hardware_simulator` tree absorb at cppp `plugins/` (pre-thin approach) — HS stays the nested vendor submodule.
- WinUHid driver / `WinUHid.dll` (host-installed via UI guide button; not bundled).
