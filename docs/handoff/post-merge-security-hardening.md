# Post-merge security hardening (main tip → findings fix)

**Baseline tip:** `e7cc1a1` (privacy + terminal + file + VHID)  
**Findings source:** Project `docs/reviews/main-post-merge-security.md`  
**Patch:** `patches/0007-post-merge-security-hardening.patch`

## Choices

| Finding | Choice |
|---------|--------|
| Medium #1 shared reliable channel | **Priority + `bufferedAmount` backpressure** on the existing `userInput` channel (no second SCTP stream). Control (privacy opcode, file/term JSON) sends immediately; bulk (file/term binary chunks) waits above 256 KiB / resumes at 64 KiB. UI tip once per session when bulk backpressure engages. |
| Medium #2 file auto-accept | **Desktop default `fileXferAutoAccept = false`** (explicit confirm). Terminal stays available under product trust: **authenticated controller = full trust** (shell / input). Auto-accept is an optional convenience switch, independent of that trust model. |
| Medium #3 blankDisplay exclusive ↔ VHID | On blankDisplay / `VDISPLAY_OCCUPY`, host **temporarily prefers SendInput**; restores prior VHID preference when clear. Native absolute path still falls through to SendInput on map failure; comments document the topology/`screenId=0` mapping. |
| Low #4 privacy singleton | **Per-session mode map** + strongest-wins recompute (`PrivacySessionModes`). One controller force-off cannot clear another session’s blank/privacyScreen. |
| Low #5 floating menu indices | **`StreamingFloatingMenuAction` enum** + aligned icon list (privacy / file / terminal / close). |

## Replay

```bash
scripts/submodule-init.sh
scripts/apply-patches.sh   # 0001…0007
cd vendor/cloudplayplus && flutter pub get
flutter test test/reliable_channel_gate_test.dart \
  test/privacy_session_modes_test.dart \
  test/streaming_floating_menu_test.dart
cd ../../plugins/session_file_transfer && dart test
```

## Owned paths (0007 + plugins)

See `patches/post-merge-security/FILE_LIST.md`.
