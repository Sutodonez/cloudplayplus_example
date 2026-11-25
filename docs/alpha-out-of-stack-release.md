# Alpha release — out-of-stack punch trial

**Updated:** 2026-11-25 Asia/Shanghai (UTC+8) — **overwrite** after Medium+ + CI green

## Version

| Field | Value |
|-------|--------|
| **Version string** | `0.1.0-alpha.out-of-stack+bf7f886` |
| **Release tag** | `v0.1.0-alpha.out-of-stack` (GitHub **prerelease**, overwritten) |
| **Binary tip SHA** | `bf7f8865484146e0924a93caedde22b04e1357c5` |
| **Trial git tag** | `trial/out-of-stack-punch` @ same tip |
| **PR** | [#14](https://github.com/Sutodonez/cloudplayplus_plus/pull/14) |
| **Supersedes** | `0.1.0-alpha.out-of-stack+045e380` |

### Scheme

- Out-of-stack trial alpha: `0.1.0-alpha.out-of-stack+<tip7>`
- Future in-stack: `0.1.0-alpha.in-stack+<tip7>` — shares major.minor `0.1.0`
- `+<tip7>` = **binary** tip (CI Windows Release)

### What’s in this overwrite vs +045e380

- Medium+ hardening (punch target validation, serialize bursts, forceRelay TURN gate, async punch)
- MSVC C4996 `sscanf` fix (manual IPv4 parse)
- Corrected `0010` hunk so SymmetricPunch is not truncated
- Windows Desktop CI **success** on tip (`FACT`)

## Artifact

| Delivery | Path / URL |
|----------|------------|
| **GitHub prerelease** | https://github.com/Sutodonez/cloudplayplus_plus/releases/tag/v0.1.0-alpha.out-of-stack |
| Zip asset | `cppp-trial-oos-0.1.0-alpha+bf7f886-windows-x64.zip` (~22 MiB) |
| Store copy | `/cursor/stores/bc-629b0d73-f4bd-4b78-aeac-c8a782406c3c/media/cppp-trial-oos-0.1.0-alpha+bf7f886-windows-x64.zip` |
| SHA256 | `b34cd316e3afa66971982d7d913088aa4b992b4b53fe82eec585a9dbf1cc1ae9` |
| CI source | [run 45639435762](https://github.com/Sutodonez/cloudplayplus_plus/actions/runs/45639435762) `windows-bundle` |

**Form:** portable Flutter Windows Release folder zip（开包即用）. No MSIX/Inno/NSIS.

## How to run

1. Download the zip from the Release (or store path)  
2. Extract; keep `data/` + DLLs next to `cloudplayplus.exe`  
3. Run `cloudplayplus.exe`  
4. 网络设置 →「NAT 穿透 / 打洞」→ `enablePunch` / `forceRelay`  
5. Full matrix: [`trial-out-of-stack-howto.md`](./trial-out-of-stack-howto.md)

## Limits

- Does **not** merge punch to `main`  
- Does **not** satisfy in-stack PortAllocator merge gate  
