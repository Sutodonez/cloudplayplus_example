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

# Windows checkouts may use CRLF; patches are LF. Prefer native git flag when
# available; otherwise strip CR from tracked text before applying.
APPLY_OPTS=(--index --whitespace=nowarn)
if git -C "$VENDOR" apply -h 2>&1 | grep -q -- '--ignore-cr-at-eol'; then
  APPLY_OPTS+=(--ignore-cr-at-eol)
else
  echo "==> Normalizing CRLF in vendor (git apply lacks --ignore-cr-at-eol)"
  # Only touch text-like paths that patches may use as context.
  while IFS= read -r -d '' f; do
    # Skip obvious binaries
    case "$f" in
      *.png|*.jpg|*.jpeg|*.gif|*.webp|*.ico|*.dll|*.so|*.dylib|*.exe|*.bin) continue ;;
    esac
    # Strip CR in place when present
    if grep -q $'\r' "$f" 2>/dev/null; then
      sed -i 's/\r$//' "$f"
    fi
  done < <(git -C "$VENDOR" ls-files -z)
  # Re-stage normalized content so --index apply matches the worktree.
  if [[ -n "$(git -C "$VENDOR" status --porcelain)" ]]; then
    git -C "$VENDOR" add -A
  fi
fi

for patch in "${patches[@]}"; do
  echo "==> Applying $patch"
  git -C "$VENDOR" apply "${APPLY_OPTS[@]}" "$ROOT/$patch"
done

echo "==> Applied ${#patches[@]} patch(es). Review with: git -C $VENDOR status"
