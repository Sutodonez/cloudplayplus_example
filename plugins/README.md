# cppp plugins

Place **CloudPlayPlus Plus** plugins here.

| Plugin | Role |
|--------|------|
| [`session_terminal_link`](./session_terminal_link/) | Server terminal / terminal linking over the session data channel |
| [`privacy_blank_display`](./privacy_blank_display/) | Host privacy / blank display (防窥) — Windows overlay + monitor blank |
| [`session_file_transfer`](./session_file_transfer/) | Session file/folder transfer over the data channel |

Upstream CPP plugins live under `vendor/cloudplayplus/plugins/` — do not duplicate them at this path.

Prefer path dependencies into the vendor pin when a plugin needs CPP packages; see [docs/layout.md](../docs/layout.md).

## Notes

- **NAT punch / ICE ladder** is patch-only (`patches/0009`–`0010` + `patches/nat-punch/`). It forks `vendor/.../plugins/flutter-webrtc` in-place rather than vendoring a second copy here.
