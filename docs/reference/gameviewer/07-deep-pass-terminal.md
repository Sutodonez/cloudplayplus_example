# Deep pass — remote terminal (Server + conpty_bridge + uuyc-mux)

**Date:** 2026-11-20  
**Targets:**  
- `GameViewerServer.exe` terminal business  
- `conpty_bridge.exe`, `uuyc-mux.exe`, `conpty.dll`, `OpenConsole.exe`  
**Methods:** String/RTTI; Ghidra on `conpty_bridge.exe` (argv parsers); **Ghidra on Server** `FUN_140714230` (`Terminal.MuxControl` / `terminal_mux_control_server.cpp`) — see `09-deep-pass-server-ghidra.md`.

## Module split (FACT)

| Layer | Module | Role |
|-------|--------|------|
| Orchestration | `GameViewerServer.exe` `host::business::terminal::*` | Session lifecycle, mux control server, output delivery, visible attach |
| Bridge process | `conpty_bridge.exe` | Spawned helper; args `--uuyc-mux-session`, `--uuyc-mux-config`, `--uuyc-mux-attach-existing`; loads `conpty.dll` |
| Multiplexer | `uuyc-mux.exe` (Product=`psmux` 3.4.0) | tmux-compatible Windows mux (psmux fork) |
| PTY | `conpty.dll` + `OpenConsole.exe` | Windows Terminal ConPTY stack |
| CLI | `uuyc-cli.exe` | `term` (remote) / `lterm` (local) |

Server source files (breadcrumbs):

- `terminal_manager.cpp` — `TerminalManager::handleMuxControlRequest`
- `terminal_session.cpp` — `killUuycMuxSession`, session open/close
- `terminal_mux_control_server.cpp` — IPC accept/decode/encode
- `terminal_output_delivery.cpp` — stdout/open/exit framing to controller
- `visible_mux_attach.cpp` / `visible_attach_ipc_server.cpp` — Windows Terminal UI attach
- Shared types: `shared::terminal::mux_control::{Request,Response}`

Evidence: `Output\source-path-breadcrumbs.txt`, `Output\server-terminal-deep.txt`.

## Open pipeline (OBSERVATION from structured logs)

`terminal_open` stages involving mux:

1. `terminal open decision=allow session_id=`
2. `terminal bridge result=started operation=terminal_open`
3. `terminal uuyc_mux clipboard` (`set_clipboard`)
4. `terminal uuyc_mux query` (`has_session`)
5. `terminal uuyc_mux ready` (`initial_ready` → `visible_ready`)
6. `terminal open result=success` / timeout `code=503 error=terminal_open_timeout`

Mux control IPC (`terminal_mux_control`):

- `stage=listen` → `accept_wait` → `accepted`
- `decode_request` / `encode_response` / `write_response`
- `impersonate` (user token for config under LocalAppData)
- Failures named with `server_name=` → **INFERENCE:** Windows named-pipe (or equivalent) server identity, not a fixed documented path recovered yet

Config file creation under user profile (`create_uuyc_mux_config_*`, `resolve_uuyc_mux_local_app_data_*`); psmux configs also documented at `%USERPROFILE%\.config\uuyc-mux\uuyc-mux.conf`.

## Visible attach (FACT)

- Locates Windows Terminal settings:  
  `Packages/Microsoft.WindowsTerminal_8wekyb3d8bbwe/LocalState/settings.json`  
  (+ Preview package path)
- `findSupportedWindowsTerminal` / `findWindowsTerminalSettingsPath`
- Separate cleanup path: `terminal visible attach cleanup …`

## Protobuf / features (FACT)

- `gv_pb.TerminalSessionChanged`
- Feature/type token `CT_TERMINAL`
- CLI: `uuyc-cli term -d DEVICE {new,attach,ls,kill,rename,has}` and `lterm` local equivalents (`--shell cmd`)

## Likely call path (INFERENCE)

```
Controller / uuyc-cli term
  → Server TerminalManager (session allocate)
  → start terminal_mux_control_server (named IPC, server_name=…)
  → spawn conpty_bridge.exe --uuyc-mux-session … --uuyc-mux-config …
       → uuyc-mux (psmux) + ConPTY/OpenConsole
  → terminal_output_delivery (encode stdout/exit → session channel)
  → optional visible_mux_attach (Windows Terminal settings + IPC)
  → TerminalSessionChanged notify
```

## IPC identity (FACT)

- Server logs `Terminal.MuxControl` and uses **`CreateNamedPipe` / `CreateNamedPipeW`** (`server-mux-ipc-literals.txt`).
- Mux control logs use `server_name=`; CLI client logs use `endpoint=` — same channel, different role wording (**INFERENCE:** named-pipe endpoint, possibly derived from `Terminal.MuxControl` + session id). Exact pipe path format still **UNKNOWN**.

### Ghidra — `FUN_140714230` (`terminal_mux_control_server.cpp`)

Decompiled accept/listen loop logs: `impersonate` → `started server_name=` → `accept_wait` → `accepted` / `failed stage=accept` / `failed stage=listen`. `server_name` is a runtime buffer on the control object (`param_1+0x48`), not a fixed literal. Artifact: `server-MuxControl-site.c`.

### Ghidra — `FUN_1407017b0` (`conpty_bridge.exe` locator)

Resolves `L"conpty_bridge.exe"` to a filesystem path and probes with `GetFileAttributesW`; returns empty if missing. Artifact: `server-conpty_bridge-site.c`.

### Ghidra — `FUN_1407032a0` (bridge spawn / argv) — FACT

Caller of the locator in `terminal_session.cpp` (`Server.Terminal`). Creates three inherit pipes, builds cmdline (`--shell` powershell|cmd, `--cols`/`--rows`, `--stdin/stdout/ctl-handle`, `--uuyc-mux-*`, `--display-name`), spawns with **`CreateProcessAsUserW`** flags `0x80408`. Artifact: `server-pathcaller-703515.c`. Details in `09-deep-pass-server-ghidra.md`.

### Ghidra — `FUN_14070d3d0` (visible-attach fallback) — FACT

Second locator caller: Windows Terminal visible attach with fallbacks (`windows_terminal_config_unavailable` → powershell/cmd, elevated profile, create_process/assign_job/resume/wait_ready). Artifact: `server-pathcaller-70d56b.c`.

## Ghidra notes (conpty_bridge) — FACT

Ghidra import of `conpty_bridge.exe` succeeded. UTF-16 string xrefs:

| String | Address | Code xrefs |
|--------|---------|------------|
| `uuyc-mux.exe` | `0x1404a9358` | (inventory) |
| `--uuyc-mux-session` | `0x1404a94d8` | `0x1400cbc35`, `0x1400d44bd` |
| `--uuyc-mux-config` | `0x1404a9508` | (same parsers) |
| `--uuyc-mux-attach-existing` | `0x1404a9538` | (same parsers) |
| `conpty.dll` | `0x1404a9f10` | (inventory) |

### `FUN_1400cba40` — primary argv parser (decompiled)

Parses wide argv into a config struct:

- `--shell`, `--cols`, `--rows`, `--display-name`
- `--stdin-handle`, `--stdout-handle`, `--ctl-handle` (hex handle values via `wcstoull`)
- `--uuyc-mux-session`, `--uuyc-mux-config`
- `--uuyc-mux-attach-existing` (boolean flag)

Saved: `Output\conpty-bridge-argv-parse-FUN_1400cba40.c`

### `FUN_1400d4180` — visible-attach / IPC argv parser (decompiled)

- `--visible-attach`
- `--ipc-server` (stores server/endpoint string)
- `--session-id`, `--attempt-token`, `--candidate-type`
- `--uuyc-mux-session`

Saved: `Output\conpty-bridge-visible-attach-FUN_1400d4180.c`

**INFERENCE:** Bridge receives inherited/passed HANDLEs for stdio + control channel from Server, optionally attaches to an IPC server for visible Windows Terminal integration, and drives `uuyc-mux` by session/config paths.

PDB `conpty_bridge.pdb` referenced but not loaded — recovered names are Ghidra `FUN_*`.

## Evidence index

- `D:\Documents\Projects\.REA_Library\GameViewer\Output\server-terminal-curated.txt`
- `D:\Documents\Projects\.REA_Library\GameViewer\Output\server-terminal-deep.txt`
- `D:\Documents\Projects\.REA_Library\GameViewer\Output\terminal-ipc-pipe-hints.txt`
- `D:\Documents\Projects\.REA_Library\GameViewer\Output\server-mux-ipc-literals.txt`
- `D:\Documents\Projects\.REA_Library\GameViewer\Output\conpty-bridge-argv-parse-FUN_1400cba40.c`
- `D:\Documents\Projects\.REA_Library\GameViewer\Output\conpty-bridge-visible-attach-FUN_1400d4180.c`
- `D:\Documents\Projects\.REA_Library\GameViewer\Output\cli-bridge-fn-1400cbc35.json`
- `D:\Documents\Projects\.REA_Library\GameViewer\Output\cli-bridge-fn-1400d44bd.json`
