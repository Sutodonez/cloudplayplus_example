# GameViewer inventory (first pass)

**Target:** NetEase UU Remote / 网易UU远程 (`GameViewer`), version **4.48.1.5606**  
**Input root:** `D:\Documents\Projects\.REA_Library\GameViewer\Input\GameViewer`  
**Canonical tree analyzed:** `Input\GameViewer\4.48.1.5606` (also mirrored under `bin\` / `bak\`)  
**Method:** Static layout + PE metadata + REA `inspect_desktop_application` + ASCII/UTF-16 string extraction + PE import sampling. No installer execution; no live remote session.

## Layout roles

| Path | Role |
|------|------|
| `4.48.1.5606\` | Active versioned payload (preferred analysis tree) |
| `bin\` | Parallel/current runtime copy (slightly different sizes than versioned tree) |
| `bak\` | Previous/backup payload |
| `config\` | Local runtime config (display, streamer codec cache, UI sensors) |
| `setup\` | Installer package (`UURemote_Setup_4.48.1.5606_*.exe`) |
| `plugins\` / `html\` | Qt plugins + WebView2 UI skeletons / bridge |
| `drivers\` | Virtual display / input / audio / gamepad drivers |
| Root `GameViewer.exe` / `GameViewerService.exe` | Thin/older entry stubs vs versioned binaries |

## First-party / product binaries (roles)

Evidence: PE `FileVersionInfo` ProductName/Description = 网易UU远程 / UU Remote; string PDB/source paths under `nrd-windows-client-gitlab`.

| Module | Approx size | Observed role |
|--------|-------------|----------------|
| `GameViewer.exe` | ~78 MB | Controller UI (Qt5 + WebView2) |
| `GameViewerLauncher.exe` | ~10 MB | Launch/bootstrap |
| `GameViewerServer.exe` | ~34 MB | Host/server core: session, input, display, terminal, port mapping |
| `GameViewerService.exe` | ~8 MB | Windows service wrapper (`apps/service`) |
| `GameViewerHealthd.exe` | ~11 MB | Health monitor + cloud API helpers |
| `streamer.dll` | ~20 MB | Media + P2P transport (WebRTC fork + KCP/QUIC extensions) |
| `StreamerCodecDetector.exe` | ~3.9 MB | Encoder/decoder capability probe |
| `uuyc-cli.exe` | ~12 MB | CLI control plane (devices, terminal, input diag) |
| `uuyc-mux.exe` | ~10 MB | Terminal multiplexer (**psmux** fork; Product=`psmux`) |
| `conpty_bridge.exe` | ~6.5 MB | Bridge into ConPTY / `uuyc-mux` |
| `conpty.dll` | ~110 KB | Windows Terminal ConPTY library |
| `OpenConsole.exe` | ~1 MB | Console PTY host (Windows Terminal) |
| `nemu-api.dll` / `remote-nemu-api.dll` | ~10 / ~5 MB | NetEase emulator (NEMU) integration |
| `Nevaudiosdk.dll` | ~1.7 MB | Virtual/remote audio |
| `nrd_renderer_ipc.dll` | ~185 KB | NRD renderer IPC |
| `aria2c.exe` | ~6 MB | Download helper |
| `PsExec64.exe` | ~0.8 MB | Sysinternals helper (session/privilege) |
| `DriverHelper.exe` / `devcon.exe` | drivers helper | Driver install |
| `Upgrade.exe` / `Uninstall.exe` / `cleanup_utils.exe` / `crashpad_handler.exe` | lifecycle | Update / uninstall / cleanup / crash |

Machine type for examined PE headers: **x64** (`machine: 34404`).

## Drivers

| Driver | Class | Likely purpose |
|--------|-------|----------------|
| `GameViewerIddDriver` (UMDF DLL) | Display | Indirect Display Driver (virtual display / privacy screen) |
| `uuycinput.sys` | System + VHF lower filter | Virtual HID input bus (`netease\uuycinput`) |
| `uuycinputmf.sys` | Mouse upper filter | Mouse filter (`HID\VID_5E2A&PID_71B4&Col03`) |
| `ViGEmBus.sys` | System | Nefarius virtual gamepad bus (OSS) |
| `nevaudio.sys` | MEDIA | NetEase virtual audio device |

## Bundled OSS / third-party (from `licenses.txt` + strings)

WebRTC, Qt5, OpenSSL 3, protobuf, abseil, asio, curl, poco, cryptopp, libyuv, FreeImage, websocketpp, sentry-native/crashpad, ViGEmBus, psmux, Windows Terminal ConPTY/OpenConsole, IddDriver (MS-PL), aria2, zlib, nlohmann-json, spdlog, vcpkg.

## Supporting JSON inventories

- `inventory-first-party.json`
- `inventory-drivers.json`
- `rea-desktop-inspect.json` (REA Evidence dump)
- `string-scan-summary.json`
