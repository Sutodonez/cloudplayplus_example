# Enhanced / hard-NAT hole punch

**Origin PR:** [#1](https://github.com/Sutodonez/cloudplayplus_plus/pull/1)  
**Trial tag:** `trial/out-of-stack-punch` (out-of-stack path on tip that includes main overlay + renumbered punch patches)  
**Layout:** thinned cppp — patches onto `vendor/cloudplayplus` pin (not a pre-thin monorepo tree)

## What ships

| Piece | Detail |
|-------|--------|
| Punch | Firewall UDP probes to `119.29.29.29` / `223.5.5.5`; symmetric multi-socket bursts to remote `srflx`/`host` |
| Soft ICE | Concurrent STUN+TURN when `enablePunch` + TURN; `iceTransportPolicy: all` |
| forceRelay | `iceTransportPolicy: relay` + TURN |
| Dart flags | `StreamingSettings.enablePunch` / `forceRelay` + network settings toggles |
| Native | flutter-webrtc MethodChannel `natPunchProbeFirewall` / `natPunchSymmetric` (Dart `RawDatagramSocket` fallback) |

## Replay surface

- `patches/0009-nat-punch-ice-policy-and-wireup.patch`
- `patches/0010-nat-punch-flutter-webrtc-methodchannel.patch`
- Ownership / bump conflicts: `patches/nat-punch/FILE_LIST.md`

## Gaps (unchanged from feature authorship)

- In-stack PortAllocator SymmetricPunch needs rebuildable libwebrtc (tree only has prebuilt binaries).
- iOS/macOS/Android native MethodChannel not wired (Dart fallback covers `dart:io` platforms).
- No automatic session restart into forceRelay after ICE failure (UI prompts the user).

## Verification

- Authored `test/ice_policy_test.dart` (candidate parse, ICE ladder, forceRelay, options JSON).
- Run inside vendor after apply: `flutter test test/ice_policy_test.dart`
- Manual NAT matrix still needed on real networks.
