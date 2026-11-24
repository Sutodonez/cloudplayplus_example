#!/usr/bin/env bash
# Build the CPP app from the vendor pin (after optional patch apply).
#
# Usage:
#   scripts/build.sh                 # flutter pub get only
#   scripts/build.sh linux
#   scripts/build.sh windows
#   scripts/build.sh macos
#   scripts/build.sh web
#   scripts/build.sh apk
#   scripts/build.sh ios
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

VENDOR="vendor/cloudplayplus"
TARGET="${1:-}"

if [[ ! -f "$VENDOR/pubspec.yaml" ]]; then
  echo "ERROR: $VENDOR/pubspec.yaml missing. Run scripts/submodule-init.sh first." >&2
  exit 1
fi

if [[ -x "$ROOT/scripts/apply-patches.sh" ]]; then
  "$ROOT/scripts/apply-patches.sh"
fi

echo "==> flutter pub get (vendor + nested plugins)"
(
  cd "$VENDOR"
  flutter pub get
  while IFS= read -r -d '' pubspec; do
    plugin_dir="$(dirname "$pubspec")"
    echo "  -> $plugin_dir"
    (cd "$plugin_dir" && flutter pub get)
  done < <(find plugins -maxdepth 2 -name pubspec.yaml -print0 2>/dev/null || true)
)

if [[ -z "$TARGET" ]]; then
  echo "==> Dependencies resolved. Pass a target to build (linux|windows|macos|web|apk|ios)."
  exit 0
fi

echo "==> Building target: $TARGET"
cd "$VENDOR"
case "$TARGET" in
  linux) flutter build linux ;;
  windows) flutter build windows ;;
  macos) flutter build macos ;;
  web) flutter build web --release ;;
  apk) flutter build apk --release --android-skip-build-dependency-validation ;;
  ios) flutter build ios --no-codesign ;;
  *)
    echo "ERROR: unknown target '$TARGET'" >&2
    exit 1
    ;;
esac
