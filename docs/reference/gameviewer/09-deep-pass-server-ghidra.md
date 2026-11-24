# Deep pass — `GameViewerServer.exe` Ghidra (mouse + terminal)

**Date:** 2026-11-20 (updated after reconnect)  
**Env:** Shared User now has `REA_GHIDRA_STARTUP_TIMEOUT_MS=2400000`, `REA_GHIDRA_DISABLED_ANALYZERS=WindowsResourceReference,Stack`, `GHIDRA_HEADLESS_MAXMEM=8G`. Process-local overrides still OK if needed.

## Mouse — backend activation

| Item | Value |
|------|-------|
| String | `input_backend_activation … requested=vhid` @ `0x1417e9dc0` |
| Xref | `0x140e03689` |
| Procedure | `FUN_140e03580` @ `0x140e03580` |
| Artifact | `server-input_backend_activation.c` |

### Behavior (FACT)

Mutexed `send_input` ↔ `vhid` switch: failures `vhid_open_failed` / `mouse_neutral_partial`; success `path=driver`; transition `input_backend_transition from=send_input to=vhid reason=probe_available`.

## Terminal — MuxControl server

| Item | Value |
|------|-------|
| String | `Terminal.MuxControl` @ `0x1416fb540` |
| Procedure | `FUN_140714230` @ `0x140714230` |
| Artifact | `server-MuxControl-site.c` |

### Behavior (FACT)

`terminal_mux_control_server.cpp` listen/accept loop: `impersonate` → `started server_name=` → `accept_wait` → `accepted` / fail stages. Runtime `server_name` buffer at object `+0x48`.

## Terminal — `conpty_bridge` path resolve

| Item | Value |
|------|-------|
| Procedure | `FUN_1407017b0` @ `0x1407017b0` |
| Artifact | `server-conpty_bridge-site.c` |

Resolves `L"conpty_bridge.exe"` + `GetFileAttributesW`. Callers (xref): `0x140703515`, `0x14070d56b`, `0x141fa3f58` (likely data).

## Terminal — bridge spawn / argv (`terminal_session.cpp`) — FACT

| Item | Value |
|------|-------|
| Xref into locator | `0x140703515` ∈ **`FUN_1407032a0`** @ `0x1407032a0` (~9.9 KiB) |
| Source path (log) | `…\server_core\business\terminal\terminal_session.cpp` |
| Logger | `Server.Terminal` |
| Artifact | `server-pathcaller-703515.c` |

### Sequence (from decompile)

1. Shell allowlist: compares requested shell to **`powershell`** / **`cmd`**; else `shell_not_allowed`.
2. Calls **`FUN_1407017b0`** — missing path → `bridge_exe_not_found`.
3. Creates **three inherit pipes** (`CreatePipe`): stdin / stdout / ctl; failures named `create_*_pipe_failed` / `set_*_pipe_flag_failed`.
4. `UpdateProcThreadAttribute` for handle inheritance list (`attribute_list_not_initialized` / `update_attribute_handle_list_failed`).
5. Builds wide command line with:
   - `L" --shell "` + `L"powershell"` or `L"cmd"`
   - `L" --cols "` / `L" --rows "`
   - `L" --stdin-handle "` / `L" --stdout-handle "` / `L" --ctl-handle "` (`0x%IX` format)
   - `L" --uuyc-mux-session "` / `L" --uuyc-mux-config "` / optional `L" --uuyc-mux-attach-existing"`
   - `L" --display-name "`
6. Spawns via **`CreateProcessAsUserW`** (token from prior setup), `lpApplicationName=NULL`, cmdline = bridge path + args, flags **`0x80408`** (= `DETACHED_PROCESS|CREATE_UNICODE_ENVIRONMENT|EXTENDED_STARTUPINFO_PRESENT`). Failure → `create_bridge_process_failed_`.
7. Post-start logs: `terminal bridge result=started … pid= mux_session=`; waits `terminal uuyc_mux ready` (`initial_ready` → `visible_ready`); mux control start failures `terminal mux control result=failed stage=start`.

Also guards: `uuyc_mux_exe_not_found`, `create_user_environment_failed_`, `terminal_bridge_unavailable`, `terminal_display_name_invalid`, `terminal_mux_session_unavailable`.

**INFERENCE:** Server owns pipe creation + argv; bridge consumes handles/session flags already mapped in `conpty_bridge` parsers.

## Terminal — visible-attach fallback — FACT

| Item | Value |
|------|-------|
| Xref | `0x14070d56b` ∈ **`FUN_14070d3d0`** @ `0x14070d3d0` |
| Artifact | `server-pathcaller-70d56b.c` |

Logs under `Server.Terminal` / `terminal_session.cpp`: `terminal visible attach result=…` with stages `build_command`, `create_process`, `assign_job`, `resume`, `wait_ready`, `register_attempt`, `ready`; fallbacks when Windows Terminal config unavailable or elevated profile (`fallback=powershell_or_cmd`); title prefix `UU Remote Terminal - `. Spawns via **`CreateProcessAsUserW`** (same as bridge open path).

## Mouse — virtual switch setting — FACT

| Item | Value |
|------|-------|
| String | `virtual_mouse_setting result=updated enabled=` @ `0x1416e8530` |
| Xref | `0x1405af0d1` ∈ **`FUN_1405aef00`** @ `0x1405aef00` |
| Source | `…\business\input\mouse\virtual_mouse_switch_setting_manager.cpp` |
| Artifact | `server-mouse-1-virtual_mouse_setting.c` |

Writes wide setting key `L"virtual_mouse_switch"` under scope `L"global"` via settings helper, stores bool on object, logs `Server.Settings` / `virtual_mouse_setting result=updated enabled=`.

## Mouse — VHID report layout probe — FACT

| Item | Value |
|------|-------|
| String | `vhid_report_layout result=failed stage=locate_device` @ `0x1417e9758` |
| Xref | `0x140dfd082` ∈ **`FUN_140dfcf80`** @ `0x140dfcf80` |
| Source | `…\support\input\input_injector.cpp` (`Server.Input`) |
| Artifact | `server-mouse-2-vhid_layout_locate.c` |

Failure stages logged include `locate_device` and `interface_instance` (+ `property_type=`). Ties relative-report discovery to the input injector (companion of `queryRelativeMouseReportBytes` support).

## Mouse — other xref notes

| Target | Result |
|--------|--------|
| `mouse_route event=` | Empty code xrefs |
| `VirtualMouseSwitchRequest` literal | Empty code xrefs (protobuf name inventory) |
| `input_backend_transition` | Xref `0x140e03917` ∈ already-decompiled `FUN_140e03580` |

## Negative xref notes (FACT)

- `KeyboardMouseRunner::` / `handleMuxControlRequest` demangle strings: empty code xrefs.
- `CreateNamedPipeW` IAT empty under this profile (MuxControl path uses other IPC helpers).

## Ops

~16–18 min re-import per CLI call. Shared env now matches the working Server profile. Windows PE Ghidra Program checkpoint still unavailable.
