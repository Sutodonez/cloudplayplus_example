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

# Windows runners often materialize LF blobs as CRLF (core.autocrlf). Unified
# diffs then fail with "patch does not apply" / "different line endings".
# Normalize vendor text + patch files to LF before apply so both sides match.
# (Build tools accept LF on Windows; do not restore CRLF after apply.)
echo "==> Normalizing vendor text EOLs to LF (Windows-safe apply)"
git -C "$VENDOR" ls-files -z | while IFS= read -r -d '' f; do
  path="$VENDOR/$f"
  [[ -f "$path" ]] || continue
  case "$f" in
    *.png|*.jpg|*.jpeg|*.gif|*.webp|*.ico|*.dll|*.so|*.a|*.lib|*.exe|*.bin|*.jar|*.zip|*.gz|*.xz|*.7z|*.pdf|*.ttf|*.otf|*.woff|*.woff2|*.mp3|*.mp4|*.wav|*.o|*.obj|*.dylib) continue ;;
  esac
  # Only rewrite files that actually contain CR to keep this fast/quiet.
  if grep -q $'\r' "$path" 2>/dev/null; then
    perl -pi -e 's/\r\n/\n/g; s/\r/\n/g' "$path"
  fi
done

for patch in "${patches[@]}"; do
  echo "==> Applying $patch"
  tmp="$(mktemp)"
  # Strip CRs so a CRLF-checked-out patch file still applies to LF vendor text.
  tr -d '\r' < "$ROOT/$patch" > "$tmp"
  # No --index: after EOL normalize, CRLF blobs no longer match the index.
  git -C "$VENDOR" apply --whitespace=nowarn "$tmp"
  rm -f "$tmp"
done

echo "==> Applied ${#patches[@]} patch(es). Review with: git -C $VENDOR status"
