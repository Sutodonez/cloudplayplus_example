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

## Workflow

1. Make a change inside a throwaway checkout of the pin (or regenerate with `git diff`).
2. Save a unified diff relative to `vendor/cloudplayplus` as the patch file root (paths inside the patch should be relative to the submodule root, e.g. `lib/...`, `pubspec.yaml`).
3. Run `scripts/apply-patches.sh` and verify `scripts/build.sh`.

Do not commit dirty ad-hoc edits in `vendor/` on the cppp branch.
