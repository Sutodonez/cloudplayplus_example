# Trial: out-of-stack hole punch

| Item | Value |
|------|-------|
| Tag | `trial/out-of-stack-punch` |
| Branch | `cursor/trial-out-of-stack-punch-434f` |
| Base `main` | `2165ba2` (Windows Desktop CI green) |
| Meaning of “trial” | Human can build Windows Flutter desktop from this tip (after `scripts/submodule-init.sh` + `scripts/apply-patches.sh` / `scripts/build.sh windows`) and exercise **out-of-stack** punch (`enablePunch` / soft ICE / MethodChannel), together with privacy / terminal / file / VHID already on `main`. |
| Human how-to | **[`docs/trial-out-of-stack-howto.md`](./trial-out-of-stack-howto.md)** — Windows build, toggles, success signals, gaps |
| Not claimed | In-stack PortAllocator SymmetricPunch; merge of #1 into `main`; closing the #1 merge gate. |

Punch patches are renumbered to `0009`/`0010` so they apply after the landed `0001`–`0008` series. Source ideas from [#1](https://github.com/Sutodonez/cloudplayplus_plus/pull/1); this branch does **not** merge #1 to `main`.

In-stack exploration forks from the tagged commit onto `cursor/trial-in-stack-punch-434f`.

## Absorption from #1 (2026-11-25)

| Claim | Kind | Evidence |
|-------|------|----------|
| #1 out-of-stack payload fully present here | **FACT** | Compared #1 `0001`/`0002` vs this tip `0009`/`0010`: identical added/removed hunk bodies (790 + 306 added lines each pair); only hunk *context* line numbers differ (rebase onto tip with `0001`–`0008` overlay) |
| Ownership docs renumbered | **FACT** | `patches/nat-punch/*`, `docs/handoff/nat-punch.md` cite `0009`/`0010` |
| No further cherry-pick needed | **FACT** | Zero missing functional lines from #1 punch patches |
| #1 kept open | **FACT** | Prefer supersession note over closing; merge-to-`main` still gated on in-stack SymmetricPunch |
