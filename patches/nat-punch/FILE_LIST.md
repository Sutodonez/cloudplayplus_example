# NAT punch — owned vendor paths

Replayable patches (applied by `scripts/apply-patches.sh`):

| Patch | Topic |
|-------|-------|
| `patches/0009-nat-punch-ice-policy-and-wireup.patch` | IcePunchOptions / IcePolicy / punch helper / session+settings+tests |
| `patches/0010-nat-punch-flutter-webrtc-methodchannel.patch` | Desktop C++ MethodChannel + Dart `NatPunch` (bounded flutter-webrtc fork) |

Numbers `0009`/`0010` follow the main series (`0001`–`0008` privacy/terminal/file/VHID/security). On the original #1 branch these were `0001`/`0002` against a thinner tip; this trial baseline rebases them after the landed overlay.

No cppp-root plugin: punch must touch CPP ICE session wiring and `plugins/flutter-webrtc` (prefs allow core CPP / flutter-webrtc when no adequate alternative). Prefer regenerating these patches over copying `flutter-webrtc` into cppp `plugins/`.

## FILE_LIST (conflict surface on upstream bump)

### App (`vendor/cloudplayplus`)

| Path | Role |
|------|------|
| `lib/services/ice/ice_punch_options.dart` | Stable Dart ABI: `enabled`, `forceRelay`, `probeHosts`, … |
| `lib/services/ice/ice_policy.dart` | Soft ICE/TURN ladder config builder |
| `lib/services/ice/ice_candidate_endpoint.dart` | Candidate line parser for punch targets |
| `lib/services/ice/nat_punch_helper.dart` | Conditional export (io / stub) |
| `lib/services/ice/nat_punch_helper_io.dart` | Firewall probe + symmetric UDP bursts |
| `lib/services/ice/nat_punch_helper_stub.dart` | Web no-op |
| `lib/global_settings/streaming_settings.dart` | `enablePunch` / `forceRelay` prefs |
| `lib/entities/session.dart` | Wire ICE config + punch on candidates |
| `lib/entities/audiosession.dart` | Same ICE/punch wiring for audio PC |
| `lib/settings_screen.dart` | Thin settings toggles |
| `test/ice_policy_test.dart` | Unit tests for policy + parser |

### Vendored `plugins/flutter-webrtc` (desktop C++ MethodChannel)

| Path | Role |
|------|------|
| `plugins/flutter-webrtc/common/cpp/include/flutter_nat_punch.h` | Native punch API |
| `plugins/flutter-webrtc/common/cpp/src/flutter_nat_punch.cc` | UDP probe + symmetric burst |
| `plugins/flutter-webrtc/common/cpp/src/flutter_webrtc.cc` | `natPunchProbeFirewall` / `natPunchSymmetric` dispatch |
| `plugins/flutter-webrtc/windows/CMakeLists.txt` | Compile `flutter_nat_punch.cc` |
| `plugins/flutter-webrtc/linux/CMakeLists.txt` | Compile `flutter_nat_punch.cc` |
| `plugins/flutter-webrtc/elinux/CMakeLists.txt` | Compile `flutter_nat_punch.cc` |
| `plugins/flutter-webrtc/lib/src/native/nat_punch.dart` | Dart MethodChannel client |
| `plugins/flutter-webrtc/lib/src/web/nat_punch.dart` | Web stub |
| `plugins/flutter-webrtc/lib/flutter_webrtc.dart` | Export `NatPunch` |

## Intentionally **not** owned

- Prebuilt `third_party/libwebrtc` binaries / PortAllocator internals (no source in tree)
- HW encode / GPU texture paths
- `hardware_simulator`, file transfer, vhid, privacy, terminal

## Replay

1. `scripts/submodule-init.sh`
2. `scripts/apply-patches.sh`
3. `cd vendor/cloudplayplus && flutter pub get`
4. Prefer: `flutter test test/ice_policy_test.dart`
5. Manual NAT matrix (Symmetric↔Cone, firewall on/off, forceRelay, TURN) on real networks

## Future PortAllocator hook

When a rebuildable libwebrtc tree is available, add a **separate** numbered patch for in-stack SymmetricPunch on ICE sockets. Keep that commit isolated from this FILE_LIST.

## Design anchors (reference only)

- GV soft→hard ladder / punch evidence — `docs/reference/gameviewer/05-deep-pass-nat-ice.md`, `08-deep-pass-nat-ghidra.md`
- Handoff notes — `docs/handoff/nat-punch.md`
