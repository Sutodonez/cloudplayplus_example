# Skeleton — future real punch patch (`0012+`)

**Not an applyable patch.** Kept under `patches/in-stack-punch/` so `scripts/apply-patches.sh` will **not** pick it up.

Scaffold MethodChannel / Dart already shipped as:

```text
patches/0011-in-stack-methodchannel-scaffold.patch
```

Generate the **real** PortAllocator glue + binary drop notes as a **new** root patch after Aorus produces artifacts, e.g.:

```text
patches/0012-in-stack-portallocator-symmetric-punch.patch
```

(plus documented DLL drop — see [`aorus-artifact-sync.md`](./aorus-artifact-sync.md)).

---

## Intended patch layers (order)

| Layer | Where | What |
|-------|--------|------|
| L0 binary drop | *outside* git patch, or companion commit | Replace `plugins/flutter-webrtc/third_party/libwebrtc/lib/win64/libwebrtc.dll` (+ `.lib`) |
| L1 wrapper export | `third_party/libwebrtc/include/**`, webrtc-sdk/libwebrtc | Narrow C++ API to allocator-owned ports |
| L2 plugin glue | `flutter_nat_punch.cc` | Flip `CPPS_IN_STACK_LIBWEBRTC_READY`; call wrapper from `InStackSymmetric` |
| L3 Dart | already in `0011` | Keep prefer-in-stack + out-of-stack fallback |

---

## MethodChannel names (registered in `0011`)

| Name | Current behavior | After DLL |
|------|------------------|-----------|
| `natPunchInStackStatus` | `available: false`, `reason: rebuild_pending` | `available: true` when linked |
| `natPunchInStackSymmetric` | same stub | Feed remotes into `SymmetricPunchToRemotes` |

Out-of-stack (unchanged): `natPunchProbeFirewall`, `natPunchSymmetric`.

---

## Acceptance before claiming “SymmetricPunch done”

1. Windows desktop build links the rebuilt DLL.  
2. With out-of-stack **off**, in-stack **on**, manual Symmetric↔Cone matrix shows punch traffic on ICE local ports.  
3. `flutter test test/ice_policy_test.dart` still green.  
4. Replay notes updated in `docs/handoff/cpp-punch-replay.md`.
