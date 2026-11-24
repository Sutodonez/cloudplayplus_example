import 'privacy_blank_display_platform_interface.dart';

/// Host-side privacy / blank-display modes (UU-style 防窥 ladder — ideas only).
///
/// * [off] — no privacy surface
/// * [blankDisplay] — power off physical monitors (Windows)
/// * [privacyScreen] — topmost black overlays excluded from desktop capture
enum PrivacyBlankMode {
  off,
  blankDisplay,
  privacyScreen,
}

/// Windows host privacy blank-display plugin.
///
/// Other platforms report [isSupported] == false; [setMode] is a no-op that
/// returns false.
class PrivacyBlankDisplay {
  PrivacyBlankDisplay._();

  static Future<bool> isSupported() {
    return PrivacyBlankDisplayPlatform.instance.isSupported();
  }

  static Future<PrivacyBlankMode> getMode() async {
    final index = await PrivacyBlankDisplayPlatform.instance.getMode();
    if (index < 0 || index >= PrivacyBlankMode.values.length) {
      return PrivacyBlankMode.off;
    }
    return PrivacyBlankMode.values[index];
  }

  /// Apply [mode]. Optional [imagePath] is reserved for a future custom
  /// screensaver image (currently ignored; overlay is solid black).
  static Future<bool> setMode(
    PrivacyBlankMode mode, {
    String? imagePath,
  }) {
    return PrivacyBlankDisplayPlatform.instance.setMode(
      mode.index,
      imagePath: imagePath,
    );
  }

  /// When the local dismiss hotkey (Ctrl+Alt+P) turns privacy off, also call
  /// LockWorkStation on Windows if enabled.
  static Future<void> setDismissLocksHost(bool enabled) {
    return PrivacyBlankDisplayPlatform.instance.setDismissLocksHost(enabled);
  }

  /// Lock the Windows workstation (optional post-session privacy).
  static Future<bool> lockWorkstation() {
    return PrivacyBlankDisplayPlatform.instance.lockWorkstation();
  }

  /// Fires when the user dismisses privacy via the host hotkey.
  static Stream<void> get onDismissedByHotkey {
    return PrivacyBlankDisplayPlatform.instance.onDismissedByHotkey;
  }
}
