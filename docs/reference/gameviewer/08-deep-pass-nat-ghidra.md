# Deep pass — `streamer.dll` Ghidra evidence (NAT / ICE / punch)

**Date:** 2026-11-20  
**CLI env used (process-local):** `REA_GHIDRA_STARTUP_TIMEOUT_MS=1800000`, `REA_GHIDRA_DISABLED_ANALYZERS=WindowsResourceReference`, **`GHIDRA_HEADLESS_MAXMEM=8G`**  
**Note:** Shared User env already has 1800000 + WindowsResourceReference. Default ~2G heap OOMs this target; 8G process-local heap succeeds. Ask coordinator to **persist `GHIDRA_HEADLESS_MAXMEM=8G`** (or ≥6G) in User env + MCP — not changed in shared env by this agent.

## Exports (decompiled)

| Export | VA | Behavior |
|--------|-----|----------|
| `ExchangeControllerInterface` | `0x180a2a6f0` | Copies host-supplied callback table via `FUN_180d162d0`, stores to globals, returns `&PTR_FUN_1812e5e90` |
| `ExchangeControlledInterface` | `0x180a2a780` | Same pattern via `FUN_180d16c90` → `&PTR_FUN_1812e5dd0` |

Artifacts: `streamer-ExchangeControllerInterface.c`, `streamer-ExchangeControlledInterface.c`, `streamer-FUN_180d162d0.c`

### Controller callback slots (FACT from `FUN_180d162d0` string wiring)

Includes: `OnReceiveMediaTrack`, `OnRemoveMediaTrack`, `OnFrameChange`, `OnReceiveControlData` / `Text` / `File` / `Binary`, `OnRoomState`, `OnSignalPush`, `OnQosStats`, **`OnNatInfo`**, `OnPeerConnectionState`, `OnConnectionStateCode`, `OnEventReport`, `OnDualNegotiateCapability`, `OnReceiveDataChannel`, `OnSignalData`, `OnSignalHandle`.

## Hole punch (decompiled)

### `PunchCheckFireWall` — `FUN_18021271c` @ `0x18021271c`

Xref from string `PunchCheckFireWall, punch_epoch:` @ `0x18104d166` → code `0x18021280e`.

**FACT:** Probes UDP reachability to hard-coded public resolvers:

- `119.29.29.29` (DNSPod)
- `223.5.5.5` (AliDNS)

Logs `firewall check connecting to …`. Clears prior punch sockets when punch epoch matches (`param_1+0x730`).

Artifact: `streamer-PunchCheckFireWall-site.c`

### `RandomSymmericPunchToCone` — `FUN_18020f8f4` @ `0x18020f8f4`

Xref from string @ `0x18104ce93` → `0x18020f95e`.

**FACT:** Lives in `p2p/base/p2p_transport_channel.cc` (log path). Uses remote STUN candidate address (`remote_stun_candidate.address:`), allocates punch sockets, tracks `punch_socket_connections_.size`.

Artifact: `streamer-RandomSymmericPunchToCone-site.c`

### `Enhanced Hole Punching` — `FUN_180207a5e` @ `0x180207a5e`

Xref from string @ `0x18104c50b` → `0x180208027`.

**FACT:** Before punch/gather, requires ICE ufrag/pwd present (`Cannot gather candidates because ICE parameters are empty ufrag:`). Logs `Enhanced Hole Punching` and **`post NatTraversal task`**. Ties punch to ICE restart / parameter readiness (`WebRTC.PeerConnection.IceRestartState` nearby).

Artifact: `streamer-EnhancedHolePunching-site.c`

## ICE / session JSON config (decompiled)

### Room / publisher config — `FUN_180b271b0` @ `0x180b271b0`

Xref `iceServers` string also hits nearby; function parses JSON-like map with keys including:

- `room_id`, `publisher`, `subscribers`, `you`, `iceServers` (immediate decode), `reconnect_buffer`

Artifact: `streamer-iceServers-site.c`

### Client / ICE / relay policy — `FUN_180b27c10` @ `0x180b27c10`

Xref `force_relay` @ `0x180b28029` lands in this function (also references `iceServers`).

**FACT — parsed fields (string literals in decompiler):**

| Key | Role (INFERENCE) |
|-----|------------------|
| `client_id` | Client identity |
| `iceServers` | Array → per-entry parse `FUN_180b2ea60` into vector (`+0x60` stride) |
| `controller_platform` | Controller OS/platform |
| `force_auto_switch_pkt_loss` / `force_auto_switch_latency` | Hard thresholds to force path switch |
| `possible_auto_switch_pkt_loss` / `*_latency` / `*_min_latency` | Soft thresholds |
| `auto_switch_network` | Enable auto network/path switch |
| `publisher_country` / `province` / `relay_isp` | Publisher geo + preferred relay ISP |
| `subscriber_country` / `province` / `relay_isp` | Subscriber side |
| `app_data` / `streamer_data` (immediates) | Opaque blobs |

Artifact: `streamer-force_relay-site.c`

## Connectivity ladder (updated INFERENCE)

```
Exchange*Interface (callback + streamer vtable)
  → session/room JSON (iceServers[], room_id, publisher/subscribers)
  → ICE gather (WebRTC PortAllocator + TURN/STUN)
  → optional Enhanced Hole Punching
       → PunchCheckFireWall (UDP probe 119.29.29.29 / 223.5.5.5)
       → RandomSymmetricPunchToCone (remote STUN candidate)
  → prefer P2P; else force_relay / auto_switch_* using ISP+loss+latency
  → OnNatInfo / OnPeerConnectionState / OnQosStats callbacks to host
```

## Ops note

Each CLI `function`/`xrefs`/`search` **re-imports** `streamer.dll` (~8–12 min with 8G heap). Prefer batching queries; Windows PE checkpoint still unavailable per REA remediation.
