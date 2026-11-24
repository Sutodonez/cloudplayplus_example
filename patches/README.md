# Patches

Ordered, replayable patches applied onto `vendor/cloudplayplus` by `scripts/apply-patches.sh`.

## Naming

Use zero-padded numeric prefixes so lexical order matches apply order:

```text
0001-short-description.patch
0002-another-change.patch
```

## Workflow

1. Make a change inside a throwaway checkout of the pin (or regenerate with `git diff`).
2. Save a unified diff relative to `vendor/cloudplayplus` as the patch file root (paths inside the patch should be relative to the submodule root, e.g. `lib/...`, `pubspec.yaml`).
3. Run `scripts/apply-patches.sh` and verify `scripts/build.sh`.

Do not commit dirty ad-hoc edits in `vendor/` on the cppp branch.
