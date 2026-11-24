# Deep pass — NAT / ICE / hole punching (`streamer.dll`)

**Date:** 2026-11-20  
**Target:** `D:\Documents\Projects\.REA_Library\GameViewer\Input\GameViewer\4.48.1.5606\streamer.dll`  
**Methods used:** PE exports; ASCII/UTF-16 string + RTTI curation; REA `open_binary` (Ghidra bound).  
**Methods blocked:** Full Ghidra import/analyze of this ~20 MiB WebRTC-derived image exceeded `REA_GHIDRA_STARTUP_TIMEOUT_MS=600000` (`provider_timeout`). Pseudocode for `ExchangeControllerInterface` not recovered in this pass.

## API surface (FACT)

Exports that matter for remoting (Intel CTL / Optimus exports omitted):

| Export | VA | Role (INFERENCE) |
|--------|-----|------------------|
| `ExchangeControllerInterface` | `0x180a2a6f0` | Controller-side vtable/interface exchange into streamer |
| `ExchangeControlledInterface` | `0x180a2a780` | Host/controlled-side interface exchange |

Evidence: REA `inspect_native_exports` → `Output` / prior Evidence; names also in `streamer-iface-strings.txt`.

## Internal architecture (FACT from RTTI / logs)

Separate product tree: `nrd/nrd-streamer` (PDB `...\nrd\nrd-streamer\streamer\build\win-x64\Release\streamer.pdb`).

Namespaces:

- `streamer::pc::ControllerPeerConnection` / `ControlledPeerConnection`
- `streamer::pc::PeerConnectionImpl<…>`
- `streamer::ControlledSession::StreamerDataChannelEventLoop`
- `streamer::IceConnection<ControlledPeerConnection>`
- Embedded stock WebRTC: `webrtc::PeerConnection`, `cricket::P2PTransportChannel`, `BasicPortAllocatorSession`, TURN/STUN ports

Config / event keys observed as string literals:

- `iceServers`
- `signaling_domain_map`
- `event_streamer_signaling_connect`
- `force_relay` / `forced_relay` / `manual_switch_relay_enabled`
- `mix_kcp` / `enable_mix_kcp` / `quic_enabled`
- `ice_full_punch` / `enable_ice_full_punch`
- `need_to_p2p_punch`

Auth / discovery headers & hosts:

- `X-NRD-AUTH`, `X-NRD-CONTROLLING`, `X-NRD-RECONN-KEY`
- `nrd_room_id`
- `whoami-ipv4.nie.netease.com` (+ `whoami_geo_query`)
- URI schemes present: `stun:`, `turn:`, `turns:` (no hardcoded public TURN hostnames recovered in this pass)

Evidence files:

- `D:\Documents\Projects\.REA_Library\GameViewer\Output\streamer-config-strings.txt`
- `D:\Documents\Projects\.REA_Library\GameViewer\Output\streamer-auth-ice-deep.txt`
- `D:\Documents\Projects\.REA_Library\GameViewer\Output\streamer-punch-media-curated.txt`
- `D:\Documents\Projects\.REA_Library\GameViewer\Output\streamer-hole-punch-vocab.txt`
- `D:\Documents\Projects\.REA_Library\GameViewer\Output\streamer-kcpquic-strings.txt`

## Hole-punch / P2P path (strong OBSERVATION)

Beyond stock ICE candidate gathering, NetEase patches cricket with an **Enhanced Hole Punching** path:

| Symbol / log | Meaning |
|--------------|---------|
| `AddAllocatedPortForPunch` | Port allocator hook dedicated to punch ports |
| `PunchCheckFireWall` on `P2PTransportChannel` | Firewall probe before/during punch |
| `OnPunchStoppedByFirewall` | Punch aborted by firewall check |
| `RandomSymmericPunchToCone` | Classic NAT-type punch (symmetric→cone) |
| `ice_full_punch` / `Set enable_ice_full_punch` | Feature flag for full punch mode |
| `need_to_p2p_punch` | Decision gate |
| `has writable p2p connection, stop punch` | Early exit once P2P writable |
| `peer connection is already p2p, skip punching` | Idempotence |
| `ice restart, reset punch_thread` | Punch tied to ICE restart |
| `no candidate group pair found, either side maybe none NAT, skip punching` | NAT-type skip |
| `unknown ice role, skip punching` | Role-gated |

Relay fallback policy (OBSERVATION):

- Collect TURN/STUN with **force relay** logging: `collect {} turn/stun server force relay … urls [{}]`
- Loss-based switch: `filter_network_monitor loss rate is too high, try to switch to relay` (UDP then TLS)
- `skip_relay_to_non_relay_connections`, `presume writable when fully relayed`
- Manual switch: `has_success_manual_switched_relay`, `attempt_switch_relay_type`

**INFERENCE:** Connectivity ladder ≈ ICE gather → optional enhanced UDP hole punch → prefer P2P; on failure/high loss force TURN relay (UDP/TLS). Exact NAT classification algorithm and TURN provisioning JSON schema remain **UNKNOWN** without decompilation.

## Media path extras (FACT)

- DcKCP (+ FEC): `DcKcpTransport`, `dckcp_*.cc`, `mix_kcp=`
- QUIC datachannel: `ngtcp2` v1.10, `OpenSSL 1.1.1w+quic`, `QuicDataChannel`
- Version log: `Init streamer version:{} nrd-webrtc version:{} success`

## Likely call path (INFERENCE)

```
GameViewerServer / Controller UI
  → LoadLibrary(streamer.dll)
  → ExchangeControllerInterface / ExchangeControlledInterface
  → ControlledSession / Controller session
  → IceConnection + PeerConnectionImpl
  → PortAllocator: STUN/TURN gather + AddAllocatedPortForPunch
  → PunchCheckFireWall / RandomSymmetricPunchToCone (if need_to_p2p_punch)
  → DTLS-SRTP media + optional DcKCP/QUIC data channels
  → UpdateIceConnectionConfig / force_relay on degradation
```

Signaling/control plane remains outside the DLL (HTTPS `*.nrd.nie.163.com`); streamer consumes `iceServers` / domain maps supplied by the session layer.

## Ghidra status / next

Superseded by **`08-deep-pass-nat-ghidra.md`**: with `STARTUP=1800000` + process-local **`GHIDRA_HEADLESS_MAXMEM=8G`**, exports and punch/ICE config functions were decompiled. Ask coordinator to persist heap in shared env; 2400000 timeout not required for this target if heap ≥6–8G.
