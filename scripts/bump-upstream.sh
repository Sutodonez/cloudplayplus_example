#!/usr/bin/env bash
# Bump the vendor/cloudplayplus submodule pin to a new upstream SHA.
#
# Usage:
#   scripts/bump-upstream.sh                 # pin to origin/main tip of the submodule remote
#   scripts/bump-upstream.sh <commit-sha>    # pin to an explicit SHA
#
# After bumping, re-run patch replay (Phase 2+) and fix conflicts only on listed paths.
# Do not commit ad-hoc edits inside vendor/ without regenerating patches.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

SUBMODULE_PATH="vendor/cloudplayplus"

if [[ ! -e "$SUBMODULE_PATH" ]]; then
  echo "ERROR: $SUBMODULE_PATH missing. Run scripts/submodule-init.sh first." >&2
  exit 1
fi

TARGET="${1:-}"

echo "==> Fetching upstream in $SUBMODULE_PATH"
git submodule update --init -- "$SUBMODULE_PATH"
git -C "$SUBMODULE_PATH" fetch --quiet origin

if [[ -z "$TARGET" ]]; then
  TARGET="$(git -C "$SUBMODULE_PATH" rev-parse origin/main)"
  echo "==> No SHA given; using origin/main => $TARGET"
else
  echo "==> Using requested SHA => $TARGET"
  git -C "$SUBMODULE_PATH" fetch --quiet origin "$TARGET" 2>/dev/null || true
fi

git -C "$SUBMODULE_PATH" checkout --quiet "$TARGET"
RESOLVED="$(git -C "$SUBMODULE_PATH" rev-parse HEAD)"

git add "$SUBMODULE_PATH"

echo "==> Staged $SUBMODULE_PATH at $RESOLVED"
echo "    Review with: git diff --cached $SUBMODULE_PATH"
echo "    Then commit the gitlink update (and replay patches in later phases)."
