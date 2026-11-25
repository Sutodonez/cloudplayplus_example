# Patches

Ordered, replayable patches applied onto `vendor/cloudplayplus` by `scripts/apply-patches.sh`.

## Naming

Use zero-padded numeric prefixes so lexical order matches apply order:

```text
0001-short-description.patch
0002-another-change.patch
```

## Current series

| Patch | Purpose |
|-------|---------|
| `0001-linux-cmake-allow-deprecated-literal-operator.patch` | Keep Linux `-Werror`, but allow `deprecated-literal-operator` so third-party `json.hpp` (via `flutter_secure_storage_linux`) does not fail CI on newer Clang/GCC. |
| `0002-privacy-blank-display-wireup.patch` | Privacy / blank display wireup — see [`privacy-blank/`](./privacy-blank/) |
| `0003-session-terminal-link.patch` | Server terminal linking — see [`terminal-link/`](./terminal-link/) |
| `0004-session-file-transfer.patch` | Session file/folder transfer — see [`file-transfer/`](./file-transfer/) |
| `0005-vhid-relative-mouse-hs.patch` | Optional WinUHid VHID mouse (relative + absolute) in nested `hardware_simulator` — see [`vhid-relative-mouse/`](./vhid-relative-mouse/) |
| `0006-vhid-relative-mouse-app-wireup.patch` | Host `useVhidMouse` settings + WinUHid install guide |
| `0007-post-merge-security-hardening.patch` | Post-merge channel / privacy / file defaults — see [`post-merge-security/`](./post-merge-security/) |
| `0008-bugbot-and-plugin-security-followup.patch` | Bugbot + plugin security follow-up — see [`bugbot-followup/`](./bugbot-followup/) |
| `0009-nat-punch-ice-policy-and-wireup.patch` | Out-of-stack NAT punch — ICE policy, Dart helper, session/settings — see [`nat-punch/`](./nat-punch/) |
| `0010-nat-punch-flutter-webrtc-methodchannel.patch` | Out-of-stack NAT punch — flutter-webrtc MethodChannel (bounded fork) |

## Workflow

1. Make a change inside a throwaway checkout of the pin (or regenerate with `git diff`).
2. Save a unified diff relative to `vendor/cloudplayplus` as the patch file root (paths inside the patch should be relative to the submodule root, e.g. `lib/...`, `pubspec.yaml`).
3. Run `scripts/apply-patches.sh` and verify `scripts/build.sh`.

Do not commit dirty ad-hoc edits in `vendor/` on the cppp branch.

## Nested plugin submodules

Some patches (for example VHID) edit files under nested plugin submodules such as
`plugins/hardware_simulator/`. Those paths are not in the vendor superproject
index; `scripts/apply-patches.sh` applies them to the working tree only. Do not
commit the resulting dirty submodule — regenerate the patch series instead.
