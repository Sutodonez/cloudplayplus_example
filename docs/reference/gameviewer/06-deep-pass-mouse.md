# Deep pass — remote mouse (`GameViewerServer.exe` + drivers)

**Date:** 2026-11-20  
**Targets:**  
- `D:\Documents\Projects\.REA_Library\GameViewer\Input\GameViewer\4.48.1.5606\GameViewerServer.exe`  
- `...\drivers\uuycinput\`, `...\drivers\ViGEmBus\`  
**Methods:** String/RTTI curation; PE import sampling; INF review; **Ghidra decompile of backend activation** (`FUN_140e03580`) — see `09-deep-pass-server-ghidra.md`.

## Ownership (FACT)

Source breadcrumbs under `server_core/business/input/`:

- `keyboard_mouse_runner.cpp` → class `host::KeyboardMouseRunner`
- `mouse/cursor_arbitrator.cpp`
- `mouse/cursor_capture_module.cpp`
- `mouse/cursor_shape_helper.cpp`
- `mouse/cursor_state_sender.cpp`
- `mouse/virtual_mouse_switch_setting_manager.cpp`
- support: `queryRelativeMouseReportBytes` in `input::support`

Evidence: `Output\source-path-breadcrumbs.txt`, `Output\server-mouse-deep.txt`.

## Feature flags / protobuf (FACT)

Session features: `device_mouse`, `simulate_mouse`, `smart_mouse`, `virtual_mouse`, `mouse_cursor`, `device_keyboard`, `device_gamepad`.

Protobuf (`gv_pb`):

- `VirtualMouseSwitchRequest` / `VirtualMouseSwitchResponse`
- CLI/command surface: `virtual_mouse_switch`, `ff_virtual_mouse_device`

Connect-time config: `KeyboardMouseRunner::onEventConnectStateChanged` consumes `shared::business_api::QueryConfigureResponse`.

## Injection backends (FACT + INFERENCE)

Logged stages (`[InputDiag] side=server`):

| Stage | Observation |
|-------|-------------|
| `mouse_route` | Routing decision |
| `mouse_inject` | Injection attempt |
| `raw_control` | Parallel path: `vigem_handled` vs `keyboard_handled` |
| `vhid_activate` | Can fail `reason=mouse_neutral_partial` |

Backend activation log:

```
input_backend_activation result=failed current=send_input requested=vhid reason=mouse_neutral_partial residue=
```

Move varieties: `mouse_move_absolute`, `mouse_move_relative`, `mouse_move_variety_relative`.

Fallback: `wetpe_ime not install use SendInput`.

**INFERENCE — dual backend:**

1. **Soft:** Win32 `SendInput` (imported; always available).
2. **Hard VHID:** NetEase `uuycinput` virtual HID (VHF lower filter) + `uuycinputmf` mouse upper filter; relative report layout via `queryRelativeMouseReportBytes` / `vhid_report_layout`.
3. **Gamepad:** ViGEmBus install/ensureReady pipeline embedded in Server (`[ViGEmDriver] …`).

Switching soft↔virtual is productized (`virtual_mouse_setting result=updated enabled=`).

## Driver hardware IDs (FACT from INF)

- Virtual HID: `netease\uuycinput`, LowerFilters=`vhf`
- Mouse filter: `HID\VID_5E2A&PID_71B4&Col03`, UpperFilters=`uuycinputmf`
- Gamepad: `Nefarius\ViGEmBus\Gen1`

Paths: `Input\GameViewer\4.48.1.5606\drivers\uuycinput\`, `...\ViGEmBus\`.

## Likely call path (INFERENCE)

```
Controller input events (session / streamer datachannel)
  → Server session feature gate (device_mouse / virtual_mouse)
  → KeyboardMouseRunner (connect: QueryConfigureResponse)
  → mouse_route
       ├─ send_input → SendInput
       └─ vhid → open uuycinput device → relative/absolute HID reports
  → optional ViGEm for gamepad (raw_control)
  → CursorArbitrator / CursorStateSender → cursor shape back to controller
  → VirtualMouseSwitch* protobuf for mode changes
```

## Evidence index

- `D:\Documents\Projects\.REA_Library\GameViewer\Output\server-mouse-curated.txt`
- `D:\Documents\Projects\.REA_Library\GameViewer\Output\server-mouse-deep.txt`
- `D:\Documents\Projects\.REA_Library\GameViewer\Output\strings-focus-GameViewerServer-exe.txt`
- Driver INFs under Input tree

## Ghidra (FACT) — `FUN_140e03580`

Xref from `input_backend_activation … requested=vhid` → `0x140e03689` ∈ `FUN_140e03580`.

Decompile shows mutexed switch between `send_input` and `vhid`, with failure reasons `vhid_open_failed` / `mouse_neutral_partial`, success `path=driver`, and transition log `input_backend_transition from=send_input to=vhid reason=probe_available`.

Artifact: `Output\server-input_backend_activation.c` / `09-deep-pass-server-ghidra.md`.

## Additional Ghidra (FACT)

- **`FUN_1405aef00`** — `virtual_mouse_switch_setting_manager.cpp`: persists `virtual_mouse_switch` under `global`, logs `virtual_mouse_setting result=updated enabled=`. Artifact: `server-mouse-1-virtual_mouse_setting.c`.
- **`FUN_140dfcf80`** — `input_injector.cpp`: `vhid_report_layout` failures (`locate_device`, `interface_instance`). Artifact: `server-mouse-2-vhid_layout_locate.c`.

`mouse_route` / `VirtualMouseSwitchRequest` string xrefs empty under this profile.
