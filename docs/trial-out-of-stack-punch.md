# Trial: out-of-stack hole punch

| Item | Value |
|------|-------|
| Tag | `trial/out-of-stack-punch` |
| Branch | `cursor/trial-out-of-stack-punch-434f` |
| Base `main` | `2165ba2` (Windows Desktop CI green) |
| Meaning of “trial” | Human can build Windows Flutter desktop from this tip (after `scripts/submodule-init.sh` + `scripts/apply-patches.sh` / `scripts/build.sh windows`) and exercise **out-of-stack** punch (`enablePunch` / soft ICE / MethodChannel), together with privacy / terminal / file / VHID already on `main`. |
| Not claimed | In-stack PortAllocator SymmetricPunch; merge of #1 into `main`; closing the #1 merge gate. |

Punch patches are renumbered to `0009`/`0010` so they apply after the landed `0001`–`0008` series. Source ideas from [#1](https://github.com/Sutodonez/cloudplayplus_plus/pull/1); this branch does **not** merge #1 to `main`.

In-stack exploration forks from the tagged commit onto `cursor/trial-in-stack-punch-434f`.
