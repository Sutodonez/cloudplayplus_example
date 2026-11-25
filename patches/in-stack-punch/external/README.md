# External rebuild patches (Option A / m125)

These files apply to **out-of-tree** checkouts (`webrtc-sdk/webrtc`, `webrtc-sdk/libwebrtc`), **not** to `vendor/cloudplayplus` via `scripts/apply-patches.sh`.

| File | Target tree | Role |
|------|-------------|------|
| [`webrtc-m125-symmetric-punch.patch`](./webrtc-m125-symmetric-punch.patch) | `webrtc-sdk/webrtc` @ frozen m125 SHA | Adds `BasicPortAllocatorSession::SymmetricPunchToRemotes` |
| [`libwebrtc-punch-api-NOTES.md`](./libwebrtc-punch-api-NOTES.md) | `webrtc-sdk/libwebrtc` @ `125.6422.08` | How to expose punch to flutter-webrtc (no full patch yet — needs PC→allocator session wiring on rebuild host) |

Apply order on Windows: see [`docs/handoff/in-stack-m125-windows-rebuild.md`](../../../docs/handoff/in-stack-m125-windows-rebuild.md).
