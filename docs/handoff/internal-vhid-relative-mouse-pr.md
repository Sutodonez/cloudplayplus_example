---
cursor:
  subagentId: "bc-074142da-dee3-5605-b0b2-451abaa35758"
---

# VHID relative mouse — implementation report

**PR:** https://github.com/Sutodonez/cloudplayplus_plus/pull/3  
**Branch:** `cursor/vhid-relative-mouse-5758`  
**Task:** REA-22

## What landed

- Windows injector (`mouse_injector` + `vhid_mouse`) behind existing `performMouseMoveRelative` / `mouseMoveR`.
- Backends: SendInput (default, SHORT split + desktop sync retry) ↔ optional WinUHid virtual HID (dynamic `LoadLibrary`).
- Host toggle `useVhidMouse` in 键鼠设置; applied at Windows init.
- Protocol untouched (`LP_MOUSEMOVE_RELATIVE`).
- Replay docs + `patch -p0` series: `docs/patches/vhid-relative-mouse/` (dry-run OK on `19dc81a`).
- `hardware_simulator` absorbed as path tree at pin `19dc81a` because creating/pushing an HS fork returned 403 from this environment.

## Verification

| Check | Result |
|-------|--------|
| Patch dry-run on clean HS `19dc81a` | Pass |
| Flutter/Dart tests | Not run (no Flutter SDK on agent) |
| Windows MSVC build / WinUHid live game | Not run |

## Gaps

- VHID needs host-installed WinUHid driver + `WinUHid.dll` (not bundled).
- Absolute mouse still SendInput-only.
- Prefer restoring HS as submodule pointing at a reachable fork when repo-create is available; until then use patch series for upstream replay.
