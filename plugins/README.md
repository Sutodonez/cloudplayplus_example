# cppp plugins

Place **CloudPlayPlus Plus** plugins here (for example session file transfer).

Upstream CPP plugins live under `vendor/cloudplayplus/plugins/` — do not duplicate them at this path.

Prefer path dependencies into the vendor pin when a plugin needs CPP packages; see [docs/layout.md](../docs/layout.md).

## Notes

- **NAT punch / ICE ladder** is patch-only (`patches/0001`–`0002` + `patches/nat-punch/`). It forks `vendor/.../plugins/flutter-webrtc` in-place rather than vendoring a second copy here.
