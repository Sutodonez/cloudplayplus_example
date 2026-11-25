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

# Windows runners / Git Bash often expose `python` or `py -3` but not `python3`.
resolve_python() {
  if command -v python3 >/dev/null 2>&1; then
    echo python3
    return 0
  fi
  if command -v python >/dev/null 2>&1; then
    echo python
    return 0
  fi
  if command -v py >/dev/null 2>&1; then
    echo "py -3"
    return 0
  fi
  echo "ERROR: need python3, python, or py -3 for LF normalize on Windows." >&2
  exit 1
}
PYTHON_BIN="$(resolve_python)"
# shellcheck disable=SC2206
PYTHON_CMD=($PYTHON_BIN)

# The upstream pin mixes LF and CRLF blobs. Normalize the worktree (and each
# patch) to LF before applying so sequential patches are portable on Windows.
normalize_lf() {
  local target="$1"
  "${PYTHON_CMD[@]}" - "$target" <<'PY'
import sys
from pathlib import Path
root = Path(sys.argv[1])
skip = {".png",".jpg",".jpeg",".gif",".webp",".ico",".dll",".so",".dylib",".exe",".bin",".jar",".aar",".zip",".gz",".7z",".pdf",".ttf",".otf"}
n = 0
paths = [root] if root.is_file() else [p for p in root.rglob("*") if p.is_file()]
for path in paths:
    if any(part in {".git", "build"} for part in path.parts):
        continue
    if path.suffix.lower() in skip:
        continue
    try:
        data = path.read_bytes()
    except OSError:
        continue
    if b"\x00" in data[:8192]:
        continue
    if b"\r" not in data:
        continue
    path.write_bytes(data.replace(b"\r\n", b"\n").replace(b"\r", b"\n"))
    n += 1
print(f"==> LF-normalized {n} path(s) under {root}")
PY
}

echo "==> Normalizing vendor worktree to LF (via $PYTHON_BIN)"
git -C "$VENDOR" config core.autocrlf false
git -C "$VENDOR" config core.eol lf
normalize_lf "$VENDOR"

tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT

for patch in "${patches[@]}"; do
  echo "==> Applying $patch"
  base=$(basename "$patch")
  # Force LF patch bytes regardless of how the file was checked out.
  "${PYTHON_CMD[@]}" - "$ROOT/$patch" "$tmpdir/$base" <<'PY'
import sys
src, dst = sys.argv[1], sys.argv[2]
data = open(src, "rb").read().replace(b"\r\n", b"\n").replace(b"\r", b"\n")
open(dst, "wb").write(data)
PY
  if ! git -C "$VENDOR" apply --whitespace=nowarn "$tmpdir/$base"; then
    echo "ERROR: failed applying $patch" >&2
    exit 1
  fi
  normalize_lf "$VENDOR"
done

echo "==> Applied ${#patches[@]} patch(es). Review with: git -C $VENDOR status"
