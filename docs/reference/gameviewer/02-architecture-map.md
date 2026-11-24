# Architecture / feature-structure map

Product identity (FACT from PE + strings): **NetEase UU Remote (网易UU远程)**, internal codenames **NRD** / **UUYC**, package id `com.netease.uuremote`.

Internal source tree (OBSERVATION from PDB/__FILE__ strings):  
`nrd-windows-client-gitlab/.../source/src/{apps,server_core,shared}` with vcpkg + embedded WebRTC.

```
                    ┌─────────────────────────────┐
                    │ Cloud / signaling APIs      │
                    │ api*.nrd.nie.163.com        │
                    └──────────────┬──────────────┘
                                   │ HTTPS control plane
          ┌────────────────────────┼────────────────────────┐
          │                        │                        │
   GameViewer.exe            GameViewerHealthd        GameViewerService
   (Qt + WebView2 UI)        (watchdog / cloud)       (SCM service)
          │                        │                        │
          └────────────┬───────────┴────────────┬───────────┘
                       │                        │
                       ▼                        ▼
              GameViewerServer.exe ◄──── session / features
                       │
       ┌───────────────┼───────────────────────────────┐
       │               │                               │
       ▼               ▼                               ▼
 streamer.dll    input + display                 terminal stack
 (WebRTC/ICE     KeyboardMouseRunner             terminal_manager
  + KCP/QUIC     uuycinput / ViGEm / IDD         conpty_bridge
  + SRTP)        virtual_display_device          uuyc-mux (psmux)
                                                 OpenConsole/conpty
```

## Focus area 1 — NAT traversal / hole punching

**Primary module:** `streamer.dll`

**Observed stack (FACT from strings/RTTI/WebRTC paths):**

- Classic WebRTC ICE: `p2p/base/{stun_port,turn_port,tcp_port,port_allocator,p2p_transport_channel,basic_ice_controller}.cc`
- DTLS-SRTP: `pc/dtls_srtp_transport`, `srtp_session`
- SDP offer/answer: `pc/webrtc_sdp`, `webrtc_session_description_factory`
- **Custom extensions:** QUIC transport (`p2p/base/quic_*.cc`, `pc/quic_data_channel`), **DcKCP** (`media/sctp/dckcp_*.cc`, flags `mix_kcp=`, `quic_enabled=`)
- Signaling is separate from media: strings `proxy not applied to signaling`, host `signaling_list` / `sni_required_signaling_list` (Healthd)

**Control-plane hosts (OBSERVATION):**

- `https://api.nrd.nie.163.com`
- `https://api-dcdn.nrd.nie.163.com`
- `https://api-event.nrd.nie.163.com/...`
- `https://api-ipv4.nrd.nie.163.com/.../wake_on_lan/info`

**Related server-side:** `server_core/business/port_mapping/port_mapping_service.cpp` (likely UPnP/NAT-PMP or mapped-port assist — **not yet decompiled**; presence is FACT, behavior UNKNOWN).

**Inference:** Media path is WebRTC-style ICE (STUN/TURN/host candidates) with NetEase transport extensions (KCP/QUIC mix). Exact hole-punch algorithm and TURN provisioning API remain UNKNOWN pending deeper analysis of `streamer.dll` + Server session setup.

## Focus area 2 — Remote mouse

**Primary module:** `GameViewerServer.exe` + drivers

**Call-path sketch (from source breadcrumbs + RTTI):**

1. Session feature flags: `device_mouse`, `simulate_mouse`, `smart_mouse`, `virtual_mouse`, `mouse_cursor`
2. `KeyboardMouseRunner` (`business/input/keyboard_mouse_runner.cpp`)
3. Mouse subsystem: `cursor_arbitrator`, `cursor_capture_module`, `cursor_shape_helper`, `cursor_state_sender`, `virtual_mouse_switch_setting_manager`
4. Injection APIs (imports/strings): `SendInput`, HID (`HidD_*`), SetupDi device install for virtual devices
5. Kernel path: `uuycinput.sys` (VHF virtual HID) + `uuycinputmf.sys` (mouse upper filter)
6. Gamepad path: bundled **ViGEmBus**
7. Protobuf: `gv_pb.VirtualMouseSwitchRequest/Response`
8. CLI: `uuyc-cli` `input_diag:mouse-move-aggregation`, `virtual_mouse_switch`

**Inference:** Dual modes — software `SendInput` simulation vs driver-backed virtual HID/mouse filter for lower-level / game-friendly input; cursor shape mirrored back to controller.

## Focus area 3 — Remote terminal

**Primary modules:** Server terminal business + ConPTY stack + psmux

**Call-path sketch:**

1. `server_core/business/terminal/{terminal_manager,terminal_session,terminal_mux_control_server,terminal_output_delivery,visible_mux_attach,visible_attach_ipc_server}.cpp`
2. Bridge process: `conpty_bridge.exe` (args `--uuyc-mux-*`, loads `conpty.dll`, spawns `uuyc-mux.exe`)
3. Multiplexer: `uuyc-mux.exe` = **psmux** (tmux-compatible on Windows, ConPTY passthrough)
4. PTY host: `OpenConsole.exe` + `conpty.dll` (Windows Terminal OSS)
5. CLI: `uuyc-cli term` (remote device) / `lterm` (local); protobuf `TerminalSessionChanged`

**Inference:** Terminal is a first-class product feature layered on OSS psmux + Windows Terminal ConPTY, orchestrated by Server and exposed via CLI/IPC — not a thin SSH wrap.

## Other noteworthy routes

| Area | Evidence | Modules |
|------|----------|---------|
| Virtual display / privacy screen | IDD driver + `virtual_display_device.cpp`, IME candidate hider | `GameViewerIddDriver`, Server |
| Virtual audio | `nevaudio` driver + `Nevaudiosdk.dll` | drivers / SDK |
| Cloud PC | API paths `/cloud_pc/...`, `cloud_device_*` sources | Healthd / Server / CLI |
| Emulator assist | `nemu-api`, `remote-nemu-api` | NEMU |
| Port mapping | `port_mapping_service.cpp` | Server |
| UI bridge | WebView2 + `UUYCBridge` JS | `html/`, Qt UI |
| Quick launch apps | `QuickLaunch*` protobuf + sources | Server / CLI |
| Device power | features `device_reboot/shutdown/lock`, WoL API | Server / Healthd |
| Update / install | `Upgrade.exe`, setup EXE, aria2 | lifecycle |

## Evidence index

- String extracts: `Output\strings-focus-*.txt`, `Output\urls-*.txt`
- Source breadcrumbs: `Output\source-path-breadcrumbs.txt`
- REA desktop inspect: `Output\rea-desktop-inspect.json`
- Driver INF text under `Input\...\drivers\**\*.inf`
