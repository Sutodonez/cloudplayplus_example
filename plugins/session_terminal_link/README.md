# session_terminal_link

Isolated Dart module for CloudPlayPlus Plus **server terminal / terminal linking**
(终端链接).

Public product reference: NetEase UU 远程「终端连接」
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
| Control | JSON envelope `{"term_link": {...}}` — open / attach / detach / kill / list / resize / input / state |
| Payload | Binary chunks with opcode `68` (`kTermChunkOpcode` / `LP_TERM_CHUNK`) |
| Host shell | `dart:io` `Process` — Windows PowerShell / macOS–Linux `$SHELL` |
| Detach | Closing the controller UI detaches only; host process keeps running; reattach replays a 64 KiB ring buffer |

## App wiring

1. Path-depend this package from the vendor app (`../../plugins/session_terminal_link`).
2. Apply `patches/0001-session-terminal-link.patch` (opcode, session hooks, floating-menu GUI).
3. Construct `TerminalLinkEngine(sendText:, sendBinary:, isHost:)` on both peers.
4. Route data-channel text/binary into `onTextMessage` / `onBinaryMessage`.

## Gaps

| Topic | Status |
|-------|--------|
| Real ConPTY / OpenConsole PTY | **Not wired** — pipe Process only; TUI (vim/htop) degraded |
| psmux / multi-pane mux | **Not bundled** — multi-session is process-map only |
| Visible Windows Terminal attach | **Not implemented** |
| Lock-screen account verification | **Not implemented** |
| Web as **host** | Unsupported (`dart:io`) |
| Web as **controller** | Supported (UI + channel) |
| UU CLI `term` / `lterm` parity | Out of scope for this slice |
| Linux host | Supported here (UU public docs currently omit Linux host) |

## Tests

```bash
cd plugins/session_terminal_link
dart pub get
dart test
```
