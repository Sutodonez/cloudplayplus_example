# Virtual HID mouse — rebase playbook (cppp layout)

**Track:** VHID mouse (SendInput ↔ optional WinUHid) for **relative + absolute**  
**Wire protocol:** unchanged — `LP_MOUSEMOVE_RELATIVE` / absolute framing + `performMouseMoveRelative` / `performMouseMoveAbsl`  
**Vendor pin:** `vendor/cloudplayplus` @ `87c0920`  
**HS pin:** nested submodule `plugins/hardware_simulator` @ `19dc81a`

## Layout

| Path | Role |
|------|------|
| `patches/0001-vhid-relative-mouse-hs.patch` | HS deltas (paths under `plugins/hardware_simulator/`) |
| `patches/0002-vhid-relative-mouse-app-wireup.patch` | CPP app settings / init / UI wireup + WinUHid install guide button |
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
- `mouseMoveA` (absolute; when VHID effective uses report id 2)

## Host dependency (optional)

- Install [cgutman/WinUHid](https://github.com/cgutman/WinUHid) UMDF driver + place `WinUHid.dll` on `PATH` / next to the app.
- Host UI: 键鼠设置 → **虚拟 HID 鼠标 (WinUHid)** switch (title + description) and **安装 WinUHid 驱动** button (opens official repo install guide).
- If driver/DLL missing, plugin falls back to SendInput for relative and absolute.

## Absolute path notes

- Relative: HID report id 1 (16-bit dx/dy + wheel).
- Absolute: HID report id 2; percent + `screenId` mapped to virtual-desktop normalized 0..65535 (multi-monitor / multi-screen ready).
- Wire framing unchanged; only the Windows host injector backend switches.

## Anti-patterns

- Do not change `LP_MOUSEMOVE_RELATIVE` framing.
- Do not re-absorb the full HS tree at cppp `plugins/`.
- Do not vendor NetEase / GameViewer binaries or decompiled VHID bodies.
- Do not bundle WinUHid driver/DLL in the app package (same mode as ViGEmBus host-install).
- Do not fold punch / file-transfer / privacy / terminal work into this series.
