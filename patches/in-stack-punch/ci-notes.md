# CI notes — in-stack punch (scaffold)

**FACT today:** GitHub Actions for this repo build Flutter desktop against the **prebuilt** `libwebrtc` drop inside `vendor/cloudplayplus/plugins/flutter-webrtc`. There is **no** depot_tools / GN / Ninja job that rebuilds WebRTC.

## Do not expect CI to

- Compile `webrtc-sdk/webrtc` or produce a new `libwebrtc.dll`
- Prove SymmetricPunch correctness (needs real NAT matrix)
- Authorize merge of #1 / #15 to `main`

## After Human picks a pin + Windows host builds a DLL

| Step | Owner | CI role |
|------|--------|---------|
| Drop binary + thin glue patches (`0011`+) on this branch | Agent / Human | Normal Windows Desktop check must stay green |
| Optional: cache rebuilt DLL as a release asset | Human | Download in a future workflow — **not** wired yet |
| NAT matrix | Human | Out of CI scope |

## Safe checks while still scaffold-only

- `scripts/apply-patches.sh` continues to apply `0001`–`0010` only (skeleton under this directory is **not** a `.patch` at `patches/*.patch`).
- Docs-only commits on `cursor/trial-in-stack-punch-434f` should not break desktop CI.

## Future workflow sketch (non-binding)

```yaml
# NOT added to the repo yet — illustration only after Human approves packaging
# - job: rebuild-libwebrtc  (self-hosted Windows, depot_tools, hours-long)
# - artifact: libwebrtc-win64-punch.dll
# - job: flutter-windows    (consumes artifact into third_party/libwebrtc/lib/win64/)
```

Until that packaging decision exists, keep rebuild **manual** on the chosen Windows host.
