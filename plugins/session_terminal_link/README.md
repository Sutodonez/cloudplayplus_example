# session_terminal_link

Isolated Dart module for CloudPlayPlus Plus **server terminal / terminal linking**
(终端链接).

Public product reference: NetEase UU 远程「终端连接»
([help](https://uuyc.163.com/help/20260509/40220_1299599.html),
[work features](https://uuyc.163.com/features/work/)).

Design reference (in-repo, no binaries):

- [`docs/reference/gameviewer/07-deep-pass-terminal.md`](../../docs/reference/gameviewer/07-deep-pass-terminal.md)
- [`docs/reference/gameviewer/09-deep-pass-server-ghidra.md`](../../docs/reference/gameviewer/09-deep-pass-server-ghidra.md)
- [`docs/reference/gameviewer/04-oss-combination-points.md`](../../docs/reference/gameviewer/04-oss-combination-points.md) (psmux + ConPTY + datachannel)

**Do not** copy NetEase helpers (`conpty_bridge.exe`, `uuyc-mux.exe`, …) or port
decompiled bodies from `docs/reference/gameviewer/artifacts/`.

## Design

| Layer | Behavior |
|-------|----------|
| Transport | Reliable WebRTC data channel (or any ordered side channel) |
| Control | JSON envelope `{"term_link": {...}}` — open / attach / detach / kill / list / resize / input / state / **split_pane** / **select_pane** / **visible_attach** |
| Payload | Binary chunks with opcode `69` (`kTermChunkOpcode` / `LP_TERM_CHUNK`) |
| Host shell (Windows) | Prefer **psmux** session + **ConPTY** attach → bare ConPTY → pipe fallback |
| Host shell (other) | `dart:io` `Process` pipes |
| Multi-pane | psmux `split-window` / `select-pane` when `psmux` is on PATH (`winget install psmux`) |
| Visible attach | Launch Windows Terminal (`wt.exe`) attached to the psmux session |
| Detach | Closing the controller UI detaches only; host process / mux keeps running; reattach replays a 64 KiB ring buffer |

## App wiring

1. Path-depend this package from the vendor app (`../../plugins/session_terminal_link`).
2. Apply `patches/0001-session-terminal-link.patch` (opcode, session hooks, floating-menu GUI).
3. Construct `TerminalLinkEngine(sendText:, sendBinary:, isHost:)` on both peers.
4. Route data-channel text/binary into `onTextMessage` / `onBinaryMessage`.
5. On Windows hosts, install [psmux](https://github.com/psmux/psmux) for multi-pane + best WT attach (`winget install psmux`).

## Gaps (deferred)

| Topic | Status |
|-------|--------|
| Lock-screen account verification | **Deferred** (pre-merge checklist Q17) |
| Web as **host** | Unsupported (`dart:io` / ConPTY) — deferred |
| Web as **controller** | Supported (UI + channel) |
| UU CLI `term` / `lterm` parity | Out of scope for this slice |
| Shared PTY when psmux absent + WT visible attach | WT launches a **separate** shell; shared attach needs psmux |

## Tests

```bash
cd plugins/session_terminal_link
dart pub get
dart test
```
