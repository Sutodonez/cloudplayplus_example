# GameViewer (网易UU远程) — analysis summary

**Project folder:** `D:\Documents\Projects\.REA_Library\GameViewer`  
**Version:** `4.48.1.5606`  
**Updated:** 2026-11-21

## Verdict

Ghidra evidence covers **NAT/ICE hole punching** in `streamer.dll` and **Server** remote mouse + terminal paths. Shared env (`STARTUP=2400000`, `DISABLED=WindowsResourceReference,Stack`, heap `8G`) matches the working Server/streamer profile.

## NAT / ICE punch (`streamer.dll`) — Ghidra FACT

Binary: GameViewer `streamer.dll` (nrd-webrtc / WebRTC fork; analyzed from local Input, **not** in this tree). Detail: [08-deep-pass-nat-ghidra.md](./08-deep-pass-nat-ghidra.md).

### Key procs / strings (FACT)

| Proc / export | Role |
|---------------|------|
| `ExchangeControllerInterface` / `ExchangeControlledInterface` | Host callback-table exchange; returns streamer vtables |
| `FUN_180d162d0` | Wires Controller callbacks including **`OnNatInfo`**, peer/QoS/signal slots |
| **`FUN_180207a5e`** | Enhanced Hole Punching: requires ICE ufrag/pwd; logs `post NatTraversal task` |
| **`FUN_18021271c`** | `PunchCheckFireWall` — UDP probes **`119.29.29.29`**, **`223.5.5.5`** |
| **`FUN_18020f8f4`** | `RandomSymmericPunchToCone` (`p2p_transport_channel.cc`) vs remote STUN candidate |
| `FUN_180b271b0` / **`FUN_180b27c10`** | Session JSON: `iceServers[]`, `client_id`, geo/`*_relay_isp`, auto-switch loss/latency; `force_relay` neighborhood |

### Flow (INFERENCE from decompiled call sites + strings)

```
Exchange*Interface
  → room/session JSON (iceServers[], room_id, publisher/subscribers)
  → ICE gather (WebRTC PortAllocator + STUN/TURN)
  → Enhanced Hole Punching (NatTraversal task)
       → PunchCheckFireWall (public DNS UDP probes)
       → RandomSymmetricPunchToCone (remote STUN candidate)
  → prefer P2P; else force_relay / auto_switch_* (ISP + loss/latency)
  → OnNatInfo / OnPeerConnectionState / OnQosStats to host
```

Confidence: punch/ICE config bodies and hard-coded probe IPs are **FACT** from decompile; ordering of the ladder and “prefer P2P then relay” is **INFERENCE**.

Artifacts: [08-deep-pass-nat-ghidra.md](./08-deep-pass-nat-ghidra.md), `artifacts/streamer-Exchange*.c`, `artifacts/streamer-PunchCheckFireWall-site.c`, `artifacts/streamer-RandomSymmericPunchToCone-site.c`, `artifacts/streamer-EnhancedHolePunching-site.c`, `artifacts/streamer-iceServers-site.c`, `artifacts/streamer-force_relay-site.c`.

## Terminal — Ghidra FACT (`GameViewerServer.exe`)

| Proc | Role |
|------|------|
| `FUN_1407017b0` | Locate `conpty_bridge.exe` |
| **`FUN_1407032a0`** | Spawn: 3×`CreatePipe` + argv + **`CreateProcessAsUserW` (`0x80408`)** (`terminal_session.cpp`) |
| **`FUN_14070d3d0`** | Visible-attach / WT fallback (`CreateProcessAsUserW`) |
| `FUN_140714230` | MuxControl listen/accept + `server_name=` |

## Mouse — Ghidra FACT (`GameViewerServer.exe`)

| Proc | Role |
|------|------|
| `FUN_140e03580` | `send_input` ↔ `vhid` activation |
| **`FUN_1405aef00`** | Persist `virtual_mouse_switch` / `global` (`virtual_mouse_switch_setting_manager.cpp`) |
| **`FUN_140dfcf80`** | `vhid_report_layout` probe failures in `input_injector.cpp` |

`mouse_route` / `VirtualMouseSwitchRequest` literals: empty xrefs. `queryRelativeMouseReportBytes` remains RTTI-named; layout injector is the practical owner.

## 通俗说明（选型参考）

给非专门技术人员、具备网络常识即可阅读的实现路线说明（对称 NAT 打洞、老游戏相对鼠标）：见 [11-tech-notes-plain.md](./11-tech-notes-plain.md)。

与 CloudPlayPlus 对照及插件迁移评估：见 [99-vs-cloudplayplus.md](./99-vs-cloudplayplus.md)。

## Artifacts

| Area | Paths in this tree |
|------|---------------------|
| **NAT / ICE** | [08-deep-pass-nat-ghidra.md](./08-deep-pass-nat-ghidra.md), `artifacts/streamer-*.c`, [05-deep-pass-nat-ice.md](./05-deep-pass-nat-ice.md) |
| Terminal | [07-deep-pass-terminal.md](./07-deep-pass-terminal.md), [09-deep-pass-server-ghidra.md](./09-deep-pass-server-ghidra.md), `artifacts/server-pathcaller-*.c`, `artifacts/server-MuxControl-site.c`, `artifacts/conpty-bridge-*.c` |
| Mouse | [06-deep-pass-mouse.md](./06-deep-pass-mouse.md), [09-deep-pass-server-ghidra.md](./09-deep-pass-server-ghidra.md), `artifacts/server-mouse-*.c`, `artifacts/server-input_backend_activation.c` |
