# CloudPlayPlus — enhanced hole punch rebase / replay playbook

**Updated:** 2026-11-24 Asia/Shanghai  
**Repo:** https://github.com/Sutodonez/cloudplayplus_plus  
**Branch hint:** `cursor/feat-enhanced-hole-punch-cc1d`  
**Owned paths:** in-repo `patches/nat-punch/FILE_LIST.md`

## Goal

After any CloudPlayPlus / `plugins/flutter-webrtc` upstream bump, re-apply hard-NAT punch without archaeology.

## What shipped (ladder design — original code)

Ideas from GV notes only (firewall probe hosts, symmetric multi-socket bursts, P2P-prefer then force_relay). No NetEase binaries or decompiled bodies.

| Layer | Behavior |
|-------|----------|
| Punch | UDP probes to `119.29.29.29` / `223.5.5.5`; multi-socket bursts to remote `srflx`/`host` candidates |
| Soft ICE | Concurrent STUN+TURN when `enablePunch` + turn; `iceTransportPolicy: all` |
| forceRelay | `iceTransportPolicy: relay` + TURN |
| Flags | `StreamingSettings.enablePunch` / `forceRelay` (+ settings UI) |
| Native | Desktop MethodChannel `natPunchProbeFirewall` / `natPunchSymmetric` (Dart fallback if missing) |

## Replay steps

1. Fetch upstream CPP (or update the flutter-webrtc pin / submodule).  
2. Confirm conflict surface ⊆ `patches/nat-punch/FILE_LIST.md`.  
3. Cherry-pick the punch commits in order (options → helper → session/settings → webrtc MethodChannel), **or** `git am patches/nat-punch/upstream/*.patch` after regenerating format-patch.  
4. Resolve only listed files; do not fold encode/UI fixes into punch commits.  
5. Run: `flutter test test/ice_policy_test.dart`  
6. Manual NAT matrix (when hardware available): Symmetric↔Cone, firewall on/off, forceRelay on/off, turn on/off.  
7. Regenerate `git format-patch` into `patches/nat-punch/upstream/` and bump any submodule pin.

## ABI freeze

- Dart: `IcePunchOptions{enabled, forceRelay, probeHosts, …}`  
- MethodChannel: `natPunchProbeFirewall`, `natPunchSymmetric`  
- Do not rename casually across CPP versions.

## Gaps / next topics (separate commits)

- In-stack PortAllocator SymmetricPunch requires rebuildable libwebrtc (not in this tree — prebuilt `.so`/`.dll`/xcframework only).  
- iOS/macOS/Android native MethodChannel not wired yet (Dart `RawDatagramSocket` fallback).  
- Automatic session restart into forceRelay after ICE failure (UI currently prompts the user).
