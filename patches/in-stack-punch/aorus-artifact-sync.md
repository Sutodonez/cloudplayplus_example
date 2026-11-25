# Aorus artifact sync (pin A)

**Sibling agent:** `bc-37184299-f4ee-5852-bcbd-dea0057a9182` (M125 Windows rebuild on Aorus)  
**This lane:** PR #15 MethodChannel / Dart scaffolding (`0011`) — no DLL required.

## When Aorus produces artifacts

Expected drop (paths relative to vendor flutter-webrtc / CPPS tree):

| Artifact | Destination |
|----------|-------------|
| Punch-capable `libwebrtc.dll` (+ `.lib`) | `plugins/flutter-webrtc/third_party/libwebrtc/lib/win64/` |
| Updated public headers (if any) | `plugins/flutter-webrtc/third_party/libwebrtc/include/` |
| Wrapper C API notes / patch | Merge into `external/libwebrtc-punch-api-NOTES.md` → real glue |

## Sync steps (this cloud agent / follow-up)

1. Confirm SHA pair still matches freeze in [`docs/handoff/in-stack-m125-windows-rebuild.md`](../../docs/handoff/in-stack-m125-windows-rebuild.md).  
2. Drop binary; do **not** fold into `0011` — emit a new root patch / binary commit (`0012+`).  
3. Set `CPPS_IN_STACK_LIBWEBRTC_READY` to `1` and wire `InStackSymmetric` to the wrapper.  
4. Windows desktop build + NAT matrix with out-of-stack **off**, in-stack **on**.  
5. Only then consider alpha `0.1.0-alpha.in-stack+<tip7>`.

## Current FACT

- `0011` registers channels and returns `available: false` / `reason: rebuild_pending`.  
- No cricket symbols are linked from the stock prebuilt DLL.
