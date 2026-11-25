import 'privacy_blank_display_platform_interface.dart';

/// Host-side privacy / blank-display modes (UU-style 防窥 ladder — ideas only).
///
/// * [off] — no privacy surface
/// * [blankDisplay] — power off physical monitors (Windows); Dart wireup
///   auto-binds exclusive virtual display (`VDISPLAY_OCCUPY`) at session start
/// * [privacyScreen] — topmost black overlays excluded from desktop capture
enum PrivacyBlankMode {
  off,
  blankDisplay,
  privacyScreen,
}

/// Dismiss-hotkey modifier bits (must match Windows plugin wire format).
class PrivacyHotkeyModifiers {
  static const int ctrl = 1;
  static const int alt = 2;
  static const int shift = 4;
  static const int win = 8;
}

/// Host dismiss hotkey (default Ctrl+Alt+P).
///
/// Validation matches the settings capture UI: at least one known modifier
/// (Ctrl/Alt/Shift/Win) and a letter / digit / F1–F12 virtual-key code.
class PrivacyHotkey {
  const PrivacyHotkey({
    required this.modifiers,
    required this.keyCode,
  });

  /// Bitmask of [PrivacyHotkeyModifiers].
  final int modifiers;

  /// Windows virtual-key code (e.g. `0x50` for P).
  final int keyCode;

  static const int knownModifierMask = PrivacyHotkeyModifiers.ctrl |
      PrivacyHotkeyModifiers.alt |
      PrivacyHotkeyModifiers.shift |
      PrivacyHotkeyModifiers.win;

  static const PrivacyHotkey defaultHotkey = PrivacyHotkey(
    modifiers: PrivacyHotkeyModifiers.ctrl | PrivacyHotkeyModifiers.alt,
    keyCode: 0x50, // 'P'
  );

  bool get hasCtrl => (modifiers & PrivacyHotkeyModifiers.ctrl) != 0;
  bool get hasAlt => (modifiers & PrivacyHotkeyModifiers.alt) != 0;
  bool get hasShift => (modifiers & PrivacyHotkeyModifiers.shift) != 0;
  bool get hasWin => (modifiers & PrivacyHotkeyModifiers.win) != 0;

  /// Digit `0`–`9`, letter `A`–`Z`, or `F1`–`F12` VK codes.
  static bool isAllowedKeyCode(int keyCode) {
    return (keyCode >= 0x30 && keyCode <= 0x39) ||
        (keyCode >= 0x41 && keyCode <= 0x5A) ||
        (keyCode >= 0x70 && keyCode <= 0x7B);
  }

  /// At least one of Ctrl/Alt/Shift/Win; unknown bits ignored for the check.
  static bool isAllowedModifiers(int modifiers) {
    return (modifiers & knownModifierMask) != 0;
  }

  /// True when modifiers and keyCode match the UI capture rules exactly
  /// (no unknown modifier bits).
  bool get isValid =>
      isAllowedModifiers(modifiers) &&
      (modifiers & ~knownModifierMask) == 0 &&
      isAllowedKeyCode(keyCode);

  /// Strip unknown modifier bits; fall back to [defaultHotkey] if still invalid.
  PrivacyHotkey sanitized() {
    final known = modifiers & knownModifierMask;
    if (known == 0 || !isAllowedKeyCode(keyCode)) {
      return defaultHotkey;
    }
    if (known == modifiers) return this;
    return PrivacyHotkey(modifiers: known, keyCode: keyCode);
  }

  /// Short label for settings UI, e.g. `Ctrl+Alt+P`.
  String get label {
    final parts = <String>[];
    if (hasCtrl) parts.add('Ctrl');
    if (hasAlt) parts.add('Alt');
    if (hasShift) parts.add('Shift');
    if (hasWin) parts.add('Win');
    parts.add(_vkLabel(keyCode));
    return parts.join('+');
  }

  static String _vkLabel(int vk) {
    if (vk >= 0x30 && vk <= 0x39) {
      return String.fromCharCode(vk);
    }
    if (vk >= 0x41 && vk <= 0x5A) {
      return String.fromCharCode(vk);
    }
    if (vk >= 0x70 && vk <= 0x7B) {
      return 'F${vk - 0x6F}';
    }
    return '0x${vk.toRadixString(16).toUpperCase()}';
  }

  Map<String, int> toMap() => {
        'modifiers': modifiers,
        'keyCode': keyCode,
      };

  factory PrivacyHotkey.fromMap(Map<dynamic, dynamic>? map) {
    if (map == null) return defaultHotkey;
    final mods = map['modifiers'];
    final key = map['keyCode'];
    return PrivacyHotkey(
      modifiers: mods is int ? mods : defaultHotkey.modifiers,
      keyCode: key is int ? key : defaultHotkey.keyCode,
    ).sanitized();
  }
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
  /// screensaver image; passing a path today throws until a whitelist loader
  /// exists (overlay remains solid black).
  ///
  /// While any non-off mode is active, the host default render endpoint is
  /// muted and restored when privacy turns off.
  static Future<bool> setMode(
    PrivacyBlankMode mode, {
    String? imagePath,
  }) {
    return PrivacyBlankDisplayPlatform.instance.setMode(
      mode.index,
      imagePath: imagePath,
    );
  }

  /// When the local dismiss hotkey turns privacy off, also call
  /// LockWorkStation on Windows if enabled.
  static Future<void> setDismissLocksHost(bool enabled) {
    return PrivacyBlankDisplayPlatform.instance.setDismissLocksHost(enabled);
  }

  /// Configure the host dismiss hotkey (rebindable; default Ctrl+Alt+P).
  ///
  /// Invalid combinations (no known modifier, or non letter/digit/F key) are
  /// sanitized to [PrivacyHotkey.defaultHotkey] before reaching native code.
  static Future<bool> setHotkey(PrivacyHotkey hotkey) {
    final safe = hotkey.sanitized();
    return PrivacyBlankDisplayPlatform.instance.setHotkey(
      safe.modifiers,
      safe.keyCode,
    );
  }

  static Future<PrivacyHotkey> getHotkey() {
    return PrivacyBlankDisplayPlatform.instance.getHotkey();
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
