# Replay surface — bugbot + plugin security follow-up

Vendor patch: `patches/0008-bugbot-and-plugin-security-followup.patch`  
(applies after `0001`…`0007`)

| Path | Change |
|------|--------|
| `lib/utils/widgets/file_transfer_settings_screen.dart` | Reload **StreamedManager** + StreamingManager on persist |
| `lib/entities/session.dart` | Terminal send throws when channel closed; `fileTransfer.dispose()` after abort |

cppp-owned (not in the patch; live at repo root):

| Path | Change |
|------|--------|
| `plugins/session_file_transfer/**` | Require sha256; chunk size cap; control/files/total caps; reject offer while busy |
| `plugins/privacy_blank_display/windows/privacy_blank_display_plugin.cpp` | Fail privacyScreen if any monitor lacks WDA overlay |
| `plugins/session_file_transfer/test/offer_limits_test.dart` | Limits + busy-offer + overrun tests |
