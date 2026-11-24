# Virtual HID / relative-mouse — rebase playbook (cppp layout)

**Track:** VHID / relative mouse (SendInput ↔ optional WinUHid)  
**Wire protocol:** unchanged — `LP_MOUSEMOVE_RELATIVE` + `performMouseMoveRelative`  
**Vendor pin:** `vendor/cloudplayplus` @ `87c0920`  
**HS pin:** nested submodule `plugins/hardware_simulator` @ `19dc81a`

## Layout

| Path | Role |
|------|------|
| `patches/0001-vhid-relative-mouse-hs.patch` | HS deltas (paths under `plugins/hardware_simulator/`) |
| `patches/0002-vhid-relative-mouse-app-wireup.patch` | CPP app settings / init / UI wireup |
| `patches/vhid-relative-mouse/00*.patch` | Same HS deltas as classic `-p0` series for a standalone HS checkout |
| `patches/vhid-relative-mouse/FILE_LIST.md` | Conflict surface |

No cppp-root `plugins/hardware_simulator` absorb — upstream HS remains the nested vendor submodule.

## Apply on thinned cppp

```bash
scripts/submodule-init.sh
scripts/apply-patches.sh
cd vendor/cloudplayplus && flutter pub get
```

`apply-patches.sh` applies nested-HS hunks without `--index` (those paths are not in the vendor superproject index). Expect `plugins/hardware_simulator` to show as a dirty submodule after apply — do **not** commit that dirtiness; regenerate patches instead.

## Apply onto a future standalone HS pin

From a clean `hardware_simulator` checkout:

```bash
cd hardware_simulator
for p in /path/to/cloudplayplus_plus/patches/vhid-relative-mouse/00*.patch; do
  patch -p0 < "$p"
done
```

Then re-copy / regenerate `0002` app wireup against the current vendor `lib/` tree.

## MethodChannel surface (keep stable)

- `setMouseInputBackend`
- `getMouseInputBackend`
- `getEffectiveMouseInputBackend`
- `isVhidMouseAvailable`
- `mouseMoveR`

## Host dependency (optional)

- Install [cgutman/WinUHid](https://github.com/cgutman/WinUHid) driver + place `WinUHid.dll` on `PATH` / next to the app.
- Toggle **虚拟 HID 相对鼠标** in 键鼠设置. If driver/DLL missing, plugin falls back to SendInput.

## Anti-patterns

- Do not change `LP_MOUSEMOVE_RELATIVE` framing.
- Do not re-absorb the full HS tree at cppp `plugins/`.
- Do not vendor NetEase / GameViewer binaries or decompiled VHID bodies.
- Do not fold punch / file-transfer / privacy / terminal work into this series.
