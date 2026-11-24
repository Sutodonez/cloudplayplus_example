#!/usr/bin/env bash
# Initialize and sync all git submodules for this repo (cppp).
# Includes vendor/cloudplayplus (untouched CPP pin) and existing plugin submodules.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

echo "==> Initializing submodules (recursive)"
git submodule update --init --recursive

PIN_PATH="vendor/cloudplayplus"
if [[ -d "$PIN_PATH/.git" ]] || [[ -f "$PIN_PATH/.git" ]]; then
  PIN_SHA="$(git ls-tree HEAD "$PIN_PATH" | awk '{print $3}')"
  if [[ -n "$PIN_SHA" ]]; then
    echo "==> Checking out recorded pin for $PIN_PATH: $PIN_SHA"
    git -C "$PIN_PATH" fetch --quiet origin "$PIN_SHA" 2>/dev/null || true
    git -C "$PIN_PATH" checkout --quiet "$PIN_SHA"
  fi
  echo "==> vendor/cloudplayplus HEAD: $(git -C "$PIN_PATH" rev-parse HEAD)"
else
  echo "WARN: $PIN_PATH is not present after submodule init" >&2
fi

echo "==> Done. Clone tip: use git clone --recurse-submodules <url>"
