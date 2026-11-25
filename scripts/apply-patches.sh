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

# Patches are LF. Force vendor worktree to LF so sequential applies match on
# Windows (where checkout / git apply may otherwise use CRLF).
echo "==> Forcing LF vendor worktree"
git -C "$VENDOR" config core.autocrlf false
git -C "$VENDOR" config core.eol lf
git -C "$VENDOR" reset --hard HEAD
python3 - <<'PY'
from pathlib import Path
root = Path("vendor/cloudplayplus")
skip = {".png",".jpg",".jpeg",".gif",".webp",".ico",".dll",".so",".dylib",".exe",".bin",".jar",".aar",".zip",".gz"}
n = 0
for path in root.rglob("*"):
    if not path.is_file() or ".git" in path.parts or "build" in path.parts:
        continue
    if path.suffix.lower() in skip:
        continue
    try:
        data = path.read_bytes()
    except OSError:
        continue
    if b"\x00" in data[:4096] or b"\r" not in data:
        continue
    path.write_bytes(data.replace(b"\r\n", b"\n").replace(b"\r", b"\n"))
    n += 1
print(f"==> Stripped CR from {n} file(s)")
PY

for patch in "${patches[@]}"; do
  echo "==> Applying $patch"
  git -C "$VENDOR" apply --whitespace=nowarn "$ROOT/$patch"
  python3 - <<'PY'
from pathlib import Path
root = Path("vendor/cloudplayplus")
skip = {".png",".jpg",".jpeg",".gif",".webp",".ico",".dll",".so",".dylib",".exe",".bin",".jar",".aar",".zip",".gz"}
for path in root.rglob("*"):
    if not path.is_file() or ".git" in path.parts or "build" in path.parts:
        continue
    if path.suffix.lower() in skip:
        continue
    try:
        data = path.read_bytes()
    except OSError:
        continue
    if b"\x00" in data[:4096] or b"\r" not in data:
        continue
    path.write_bytes(data.replace(b"\r\n", b"\n").replace(b"\r", b"\n"))
PY
done

echo "==> Applied ${#patches[@]} patch(es). Review with: git -C $VENDOR status"
