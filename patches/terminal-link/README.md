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
| Plugin (protocol + host `Process` shells + engine) | `plugins/session_terminal_link/` |
| Vendor hooks + GUI | `patches/0001-session-terminal-link.patch` |

**Not in this slice:** ConPTY/OpenConsole PTY, psmux binary, visible Windows Terminal attach, lock-screen auth, NetEase `conpty_bridge` / `uuyc-mux`.

## Apply

```bash
scripts/submodule-init.sh
scripts/apply-patches.sh
cd vendor/cloudplayplus && flutter pub get
```
