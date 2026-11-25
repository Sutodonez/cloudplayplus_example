# Terminal link patch series

Replayable vendor wiring for **server terminal / terminal linking**.

## Design anchors (in-repo)

Prefer these over any NetEase binary or decompiled body:

- [`docs/reference/gameviewer/07-deep-pass-terminal.md`](../../docs/reference/gameviewer/07-deep-pass-terminal.md) — mux / ConPTY / bridge pipeline
- [`docs/reference/gameviewer/09-deep-pass-server-ghidra.md`](../../docs/reference/gameviewer/09-deep-pass-server-ghidra.md) — Server spawn / MuxControl evidence
- [`docs/reference/gameviewer/04-oss-combination-points.md`](../../docs/reference/gameviewer/04-oss-combination-points.md) — psmux + ConPTY + datachannel combo
- [`docs/reference/gameviewer/03-implementation-routes.md`](../../docs/reference/gameviewer/03-implementation-routes.md) — Route C

Public UX reference: UU「终端连接」help / work features pages.

## This slice

| Piece | Location |
|-------|----------|
| Plugin (ConPTY FFI, psmux, WT visible attach, engine) | `plugins/session_terminal_link/` |
| Vendor hooks + Chinese GUI | `patches/0003-session-terminal-link.patch` |

**Included:** Windows ConPTY host backend; psmux multi-pane (`split_pane` / `select_pane`); Windows Terminal local visible attach; Chinese UI strings.

**Deferred:** lock-screen account verification; Web as host.

**Toolbar merge (Q2):** when combining with privacy (#9) and file (#2), order is **privacy → file → terminal** (then close). Comments in the patch mark the insertion point.

## Apply

```bash
scripts/submodule-init.sh
scripts/apply-patches.sh
cd vendor/cloudplayplus && flutter pub get
```

On Windows hosts, install psmux for multi-pane + best visible attach:

```powershell
winget install psmux
```
