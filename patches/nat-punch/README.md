# NAT punch patch series

Enhanced / hard-NAT hole punch for cppp (thinned layout). Original code only — no NetEase binaries or decompiled bodies.

## Apply order

1. **`0001-nat-punch-ice-policy-and-wireup.patch`** — `IcePunchOptions`, `IcePolicy`, Dart punch helper, session/audio/settings wireup, unit tests
2. **`0002-nat-punch-flutter-webrtc-methodchannel.patch`** — bounded flutter-webrtc fork: `natPunchProbeFirewall` / `natPunchSymmetric`

Both live at `patches/*.patch` and are applied onto `vendor/cloudplayplus` by `scripts/apply-patches.sh`. Paths inside each patch are relative to the submodule root.

## Regenerate after editing vendor

```bash
scripts/submodule-init.sh
scripts/apply-patches.sh
# edit under vendor/cloudplayplus, then:
git -C vendor/cloudplayplus add -A
git -C vendor/cloudplayplus diff --cached -- \
  lib/services/ice \
  lib/global_settings/streaming_settings.dart \
  lib/entities/session.dart \
  lib/entities/audiosession.dart \
  lib/settings_screen.dart \
  test/ice_policy_test.dart \
  > patches/0001-nat-punch-ice-policy-and-wireup.patch
git -C vendor/cloudplayplus diff --cached -- \
  plugins/flutter-webrtc/common/cpp \
  plugins/flutter-webrtc/windows/CMakeLists.txt \
  plugins/flutter-webrtc/linux/CMakeLists.txt \
  plugins/flutter-webrtc/elinux/CMakeLists.txt \
  plugins/flutter-webrtc/lib \
  > patches/0002-nat-punch-flutter-webrtc-methodchannel.patch
git -C vendor/cloudplayplus reset --hard HEAD
```

See [FILE_LIST.md](./FILE_LIST.md).
