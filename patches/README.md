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

## Workflow

1. Make a change inside a throwaway checkout of the pin (or regenerate with `git diff`).
2. Save a unified diff relative to `vendor/cloudplayplus` as the patch file root (paths inside the patch should be relative to the submodule root, e.g. `lib/...`, `pubspec.yaml`).
3. Run `scripts/apply-patches.sh` and verify `scripts/build.sh`.

Do not commit dirty ad-hoc edits in `vendor/` on the cppp branch.

## Series present

| Patch | Topic |
|-------|-------|
| `0001-nat-punch-ice-policy-and-wireup.patch` | NAT punch — ICE policy, Dart helper, session/settings — see [`nat-punch/`](./nat-punch/) |
| `0002-nat-punch-flutter-webrtc-methodchannel.patch` | NAT punch — flutter-webrtc MethodChannel (bounded fork) |

`scripts/apply-patches.sh` LF-normalizes vendor text before apply so Windows runners (CRLF checkout) can apply LF unified diffs.

Linux desktop `-Werror` / `flutter_secure_storage` `json.hpp` (`deprecated-literal-operator`) is ambient CI-track (same class as #8/#9) — not owned by this series.
