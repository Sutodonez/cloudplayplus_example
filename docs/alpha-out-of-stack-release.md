# Alpha release — out-of-stack punch trial

**Updated:** 2026-11-25 Asia/Shanghai (UTC+8)

## Version

| Field | Value |
|-------|--------|
| **Version string** | `0.1.0-alpha.out-of-stack+045e380` |
| **Release tag** | `v0.1.0-alpha.out-of-stack` (GitHub **prerelease**) |
| **Binary tip SHA** | `045e3807fc8176735c442d042d1336a475234d31` |
| **Trial git tag** | `trial/out-of-stack-punch` @ same tip |
| **PR** | [#14](https://github.com/Sutodonez/cloudplayplus_plus/pull/14) |

### Scheme

- Out-of-stack trial alpha: `0.1.0-alpha.out-of-stack+<tip7>`
- Future in-stack trial alpha (not issued yet): `0.1.0-alpha.in-stack+<tip7>` — **shares** major.minor `0.1.0`
- `+<tip7>` always names the **binary** tip (CI Windows Release), even if the trial *branch* tip later gains docs-only commits

## Artifact

| Delivery | Path / URL |
|----------|------------|
| **GitHub prerelease** | https://github.com/Sutodonez/cloudplayplus_plus/releases/tag/v0.1.0-alpha.out-of-stack |
| Zip asset | `cppp-trial-oos-0.1.0-alpha+045e380-windows-x64.zip` |
| CI source | [run 45631374592](https://github.com/Sutodonez/cloudplayplus_plus/actions/runs/45631374592) `windows-bundle` |
| SHA256 | `2c563498e1f1306eb7da770c0f876661c3006f1f11a8c71d332e216e8b55505e` |

**Form:** portable Flutter Windows Release folder zip (开包即用). No MSIX/Inno/NSIS.

## How to run

1. Download the zip from the Release  
2. Extract; keep `data/` + DLLs next to `cloudplayplus.exe`  
3. Run `cloudplayplus.exe`  
4. 网络设置 →「NAT 穿透 / 打洞」→ `enablePunch` / `forceRelay`  
5. Full matrix: [`trial-out-of-stack-howto.md`](./trial-out-of-stack-howto.md)

## Limits

- Does **not** merge punch to `main`  
- Does **not** satisfy in-stack PortAllocator merge gate  
