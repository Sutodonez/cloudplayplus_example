# In-stack punch — FILE_LIST

**Pin:** Option **A** (Human-locked).  
**Status:** root `0011-in-stack-methodchannel-scaffold.patch` landed (stubs only). Real PortAllocator punch + DLL drop still pending Aorus rebuild.

Pin doc: [`../../docs/in-stack-libwebrtc-pin-options.md`](../../docs/in-stack-libwebrtc-pin-options.md)  
Rebuild: [`../../docs/handoff/in-stack-m125-windows-rebuild.md`](../../docs/handoff/in-stack-m125-windows-rebuild.md)  
External: [`external/`](./external/)  
Aorus sync: [`aorus-artifact-sync.md`](./aorus-artifact-sync.md)

## Applyable root patch (scaffold — not “SymmetricPunch done”)

| Patch | Role |
|-------|------|
| `patches/0011-in-stack-methodchannel-scaffold.patch` | MethodChannel stubs (`rebuild_pending`), Dart prefer-in-stack, settings toggle. **Does not** link cricket symbols or claim punch works. |

## Owned vendor paths (`0011`)

| Path | Role |
|------|------|
| `plugins/flutter-webrtc/common/cpp/include/flutter_nat_punch.h` | Declares `InStackStatus` / `InStackSymmetric` |
| `plugins/flutter-webrtc/common/cpp/include/flutter_nat_punch_in_stack.h` | `CPPS_IN_STACK_LIBWEBRTC_READY` gate (0 until DLL) |
| `plugins/flutter-webrtc/common/cpp/src/flutter_nat_punch.cc` | Stub handlers → `rebuild_pending` |
| `plugins/flutter-webrtc/common/cpp/src/flutter_webrtc.cc` | Dispatch `natPunchInStackStatus` / `natPunchInStackSymmetric` |
| `plugins/flutter-webrtc/lib/src/native/nat_punch.dart` | Dart clients |
| `plugins/flutter-webrtc/lib/src/web/nat_punch.dart` | Web stubs |
| `lib/services/ice/ice_punch_options.dart` | `preferInStackPunch` |
| `lib/services/ice/nat_punch_helper_io.dart` | Prefer in-stack → fall back out-of-stack / Dart |
| `lib/services/ice/nat_punch_helper_stub.dart` | Web ctor parity |
| `lib/global_settings/streaming_settings.dart` | Pref `preferInStackPunch` |
| `lib/settings_screen.dart` | UI toggle |
| `test/ice_policy_test.dart` | JSON round-trip for new flag |

## External owned (apply on rebuild host)

| Path (webrtc-sdk/webrtc @ frozen SHA) | Role |
|------|------|
| `p2p/client/basic_port_allocator.h` | Declares `SymmetricPunchToRemotes` |
| `p2p/client/basic_port_allocator.cc` | Bursts `PortInterface::SendTo` from `ReadyPorts()` |

Patch file: `external/webrtc-m125-symmetric-punch.patch`.

## Still provisional (after Aorus DLL drop → future `0012+`)

| Path | Role |
|------|------|
| `plugins/flutter-webrtc/third_party/libwebrtc/lib/win64/libwebrtc.dll` (+ `.lib`) | Punch-capable binary |
| `plugins/flutter-webrtc/third_party/libwebrtc/include/**` | If new wrapper exports |
| Real C API wiring in `flutter_nat_punch.cc` | Flip `CPPS_IN_STACK_LIBWEBRTC_READY` |

## Intentionally not owned

`patches/nat-punch/` and root `0009`/`0010` (out-of-stack).
