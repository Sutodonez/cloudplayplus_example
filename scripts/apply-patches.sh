#!/usr/bin/env bash
# Apply ordered patches from patches/ onto vendor/cloudplayplus.
# Patch paths inside each .patch file are relative to the submodule root.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

VENDOR="vendor/cloudplayplus"
PATCH_DIR="patches"

if [[ ! -d "$VENDOR" ]]; then
  echo "ERROR: $VENDOR missing. Run scripts/submodule-init.sh first." >&2
  exit 1
fi

shopt -s nullglob
patches=("$PATCH_DIR"/*.patch)
if ((${#patches[@]} == 0)); then
  echo "==> No patches in $PATCH_DIR (nothing to apply)"
  exit 0
fi

echo "==> Ensuring clean vendor tree before apply"
if [[ -n "$(git -C "$VENDOR" status --porcelain)" ]]; then
  echo "ERROR: $VENDOR has local changes; commit/regenerate patches or reset first." >&2
  git -C "$VENDOR" status --short
  exit 1
fi

# Windows runners often check out the submodule with CRLF (core.autocrlf=true).
# Our patches are LF. Force LF in the vendor worktree before applying.
echo "==> Forcing LF checkout in vendor (autocrlf=false)"
git -C "$VENDOR" config core.autocrlf false
git -C "$VENDOR" config core.eol lf
git -C "$VENDOR" checkout -f HEAD -- .

for patch in "${patches[@]}"; do
  echo "==> Applying $patch"
  # Apply to worktree then stage — more reliable than --index across CRLF hosts.
  git -C "$VENDOR" apply --whitespace=nowarn "$ROOT/$patch"
  git -C "$VENDOR" add -A
done

echo "==> Applied ${#patches[@]} patch(es). Review with: git -C $VENDOR status"
