# libwebrtc punch API — NOTES (Option A)

**Status:** design for rebuild host; full unified diff deferred until `SymmetricPunchToRemotes` links inside a rebuilt `libwebrtc.dll` and we can reach a live `BasicPortAllocatorSession*`.

## Goal

Expose a narrow C++ API used by flutter-webrtc MethodChannel `natPunchInStackSymmetric`:

```text
bool NatPunchInStackSymmetric(peer_connection_id,
                              vector<{ip, port}>,
                              bursts_per_endpoint) -> attempts
```

## Wiring sketch (m125 / 125.6422.08)

1. From `RTCPeerConnection` impl, obtain underlying `webrtc::PeerConnectionInterface`.  
2. Walk to ICE transport / `P2PTransportChannel` → `PortAllocatorSession` (network thread).  
3. `dynamic_cast` / known type to `cricket::BasicPortAllocatorSession*`.  
4. Call `SymmetricPunchToRemotes(remotes, bursts)`.  
5. Marshal result back to MethodChannel.

**FACT:** Stock `libwebrtc` public headers do **not** expose PortAllocator sessions today — this step **requires** wrapper changes in `src/rtc_peerconnection_impl.*` (and possibly friends). Exact symbols depend on the 125.6422.08 tree after `gclient sync`.

## flutter-webrtc glue

**Scaffold (landed — `0011-in-stack-methodchannel-scaffold.patch`):**

- Channels `natPunchInStackStatus` / `natPunchInStackSymmetric` registered; return `rebuild_pending`.  
- Dart `preferInStackPunch` + helper fallback to out-of-stack (`0009`/`0010`).  
- Gate macro `CPPS_IN_STACK_LIBWEBRTC_READY` = 0 (see `flutter_nat_punch_in_stack.h`).

**After binary drop (future `0012+`):**

- Flip gate; call wrapper → `SymmetricPunchToRemotes`.  
- Version label: `0.1.0-alpha.in-stack+<tip>`.  
- See [`../aorus-artifact-sync.md`](../aorus-artifact-sync.md).

## Do not

- Claim SymmetricPunch works while stubs return `rebuild_pending`.  
- Merge to `main` before Windows NAT validation with out-of-stack **off**.
