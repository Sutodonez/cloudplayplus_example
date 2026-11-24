# Implementation-route notes (with evidence paths)

All paths are absolute on the analysis host. Confidence tags: **FACT** / **OBSERVATION** / **INFERENCE** / **UNKNOWN**.

## Protocols / wire surface

| Layer | Observation | Evidence |
|-------|-------------|----------|
| Control HTTPS | Hosts under `*.nrd.nie.163.com` | `D:\Documents\Projects\.REA_Library\GameViewer\Output\urls-GameViewerServer-exe.txt`, `urls-GameViewerHealthd-exe.txt` |
| Media/P2P | WebRTC ICE + DTLS-SRTP; optional QUIC + DcKCP mix | `Output\strings-focus-streamer-dll.txt` (paths `..\..\p2p\base\*.cc`, `mix_kcp=`, `quic_enabled=`) |
| App RPC | protobuf package `gv_pb` | Server/CLI strings (`VirtualMouseSwitch*`, `TerminalSessionChanged`, `ConnectOptions`) |
| Terminal local IPC | mux control / visible attach IPC | source breadcrumbs `terminal_mux_control_server.cpp`, `visible_attach_ipc_server.cpp` in `Output\source-path-breadcrumbs.txt` |
| UI bridge | WebView2 host objects / `UUYCBridge` | `Input\GameViewer\4.48.1.5606\html\error\uuycbridge.js` |

Exact STUN/TURN hostnames: **UNKNOWN** (schemes `stun:`/`turn:`/`turns:` present; discovery host `whoami-ipv4.nie.netease.com` observed). See deep pass `05-deep-pass-nat-ice.md` for Enhanced Hole Punching + force_relay ladder.

## Route A — NAT traversal / hole punching

**Likely path (INFERENCE from module ownership):**

1. UI/CLI selects device → Server session init (`controlled_session_services`, `device_initializer`).
2. Cloud API returns signaling / ICE server list (`signaling_list` strings in Healthd).
3. `streamer.dll` builds PeerConnection-like transport: gather host/srflx/relay candidates via STUN/TURN ports; DTLS handshake; SRTP media.
4. Optional `mix_kcp` / `quic_enabled` alter unreliable/reliable data path for gaming latency.
5. Optional `port_mapping_service` assists inbound mapping when ICE alone is insufficient.

**Key artifacts:**

- `D:\Documents\Projects\.REA_Library\GameViewer\Input\GameViewer\4.48.1.5606\streamer.dll`
- `D:\Documents\Projects\.REA_Library\GameViewer\Input\GameViewer\4.48.1.5606\GameViewerServer.exe`
- `D:\Documents\Projects\.REA_Library\GameViewer\Input\GameViewer\4.48.1.5606\GameViewerHealthd.exe`
- Evidence dump: `Output\strings-focus-streamer-dll.txt`

**Next deep-dive (not done):** Ghidra on `streamer.dll` exports + xref from Server load/`LoadLibrary`; recover ICE server config parsing and whether KCP replaces or wraps SCTP/DTLS.

## Route B — Remote mouse

**Likely path:**

1. Feature negotiation enables `device_mouse` / `virtual_mouse` / `simulate_mouse`.
2. `KeyboardMouseRunner` receives input events over session channel.
3. Mode switch via `VirtualMouseSwitch*` (`gv_pb`) and `virtual_mouse_switch_setting_manager`.
4. Soft path: `SendInput` (imported by Server / streamer).
5. Hard path: install/open `uuycinput` VHF device + mouse filter `uuycinputmf`; relative mouse report sizing (`queryRelativeMouseReportBytes`).
6. Cursor feedback: capture/render/send cursor shape (`CursorShapeHelper`, `cursor_state_sender`).
7. Gamepad: ViGEmBus install sections embedded in Server.

**Key artifacts:**

- Server: `...\4.48.1.5606\GameViewerServer.exe`
- Drivers: `...\drivers\uuycinput\`, `...\drivers\ViGEmBus\`
- INF: `uuycinput.inf`, `uuycinputmf.inf`
- Strings: `Output\strings-focus-GameViewerServer-exe.txt`
- CLI: `uuyc-cli.exe` (`input_diag:mouse-move-aggregation`)

**PE import sample (Server):** `SendInput`, `HidD_GetFeature` / `HidD_GetPreparsedData`, `SetupDi*`, `DeviceIoControl`, `GetAdaptersAddresses` — from REA `inspect_pe_imports` on Server.

## Route C — Remote terminal

**Likely path:**

1. Controller/CLI issues `term`/`lterm` commands (`uuyc-cli`).
2. Server `terminal_manager` creates `terminal_session`.
3. Spawns `conpty_bridge.exe` with `--uuyc-mux-session` / config / attach-existing.
4. Bridge loads `conpty.dll`, talks to `uuyc-mux.exe` (psmux).
5. Mux uses ConPTY + `OpenConsole.exe` for panes; output delivered via `terminal_output_delivery` / visible attach IPC.
6. Session change events: `gv_pb.TerminalSessionChanged`.

**Key artifacts:**

- `...\conpty_bridge.exe`, `conpty.dll`, `OpenConsole.exe`, `uuyc-mux.exe`, `uuyc-cli.exe`
- Server terminal sources listed in `Output\source-path-breadcrumbs.txt`
- Strings: `Output\strings-focus-conpty_bridge-exe.txt`, `strings-focus-uuyc-mux-exe.txt`, `strings-focus-uuyc-cli-exe.txt`
- License acknowledgment: `Input\...\licenses.txt` sections `# psmux`, `# conpty.dll / OpenConsole.exe`

## Build / packaging notes

- CI path style `nrd-windows-client-gitlab\work\1131\408844\source`
- Build: `x64-windows-static-md-ninja` / `static-mt-ninja` RelWithDebInfo
- Qt5 + WebView2 controller; native C++ server

## Explicit non-claims

- Did **not** run the installer or establish a remote session.
- Did **not** extract credentials, tokens, or private keys into reports.
- Exact packet formats for gv_pb beyond message names: **UNKNOWN**.
- Whether hole punching is pure ICE or ICE+custom KCP/QUIC fallback policy: **INFERENCE only**.
