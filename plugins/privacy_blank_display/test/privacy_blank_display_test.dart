import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:privacy_blank_display/privacy_blank_display.dart';
import 'package:privacy_blank_display/privacy_blank_display_method_channel.dart';
import 'package:privacy_blank_display/privacy_blank_display_platform_interface.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  final channel = MethodChannelPrivacyBlankDisplay();
  const method = MethodChannel('privacy_blank_display');

  setUp(() {
    PrivacyBlankDisplayPlatform.instance = channel;
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(method, (call) async {
      switch (call.method) {
        case 'isSupported':
          return true;
        case 'getMode':
          return 2;
        case 'setMode':
          return true;
        case 'setDismissLocksHost':
          return null;
        case 'setHotkey':
          return true;
        case 'getHotkey':
          return {'modifiers': 3, 'keyCode': 0x50};
        case 'lockWorkstation':
          return true;
      }
      return null;
    });
  });

  tearDown(() {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger
        .setMockMethodCallHandler(method, null);
  });

  test('mode enum indices match wire opcode payload', () {
    expect(PrivacyBlankMode.off.index, 0);
    expect(PrivacyBlankMode.blankDisplay.index, 1);
    expect(PrivacyBlankMode.privacyScreen.index, 2);
  });

  test('getMode maps platform index', () async {
    expect(await PrivacyBlankDisplay.getMode(), PrivacyBlankMode.privacyScreen);
  });

  test('setMode returns success', () async {
    expect(
      await PrivacyBlankDisplay.setMode(PrivacyBlankMode.blankDisplay),
      isTrue,
    );
  });

  test('default hotkey label is Ctrl+Alt+P', () {
    expect(PrivacyHotkey.defaultHotkey.label, 'Ctrl+Alt+P');
  });

  test('hotkey validation matches UI (letter/digit/F + modifiers)', () {
    expect(PrivacyHotkey.defaultHotkey.isValid, isTrue);
    expect(
      const PrivacyHotkey(modifiers: 1, keyCode: 0x41).isValid,
      isTrue,
    );
    expect(
      const PrivacyHotkey(modifiers: 2, keyCode: 0x31).isValid,
      isTrue,
    );
    expect(
      const PrivacyHotkey(modifiers: 4, keyCode: 0x70).isValid,
      isTrue,
    );
    // No modifiers.
    expect(
      const PrivacyHotkey(modifiers: 0, keyCode: 0x50).isValid,
      isFalse,
    );
    // Unsupported VK (Escape).
    expect(
      const PrivacyHotkey(modifiers: 3, keyCode: 0x1B).isValid,
      isFalse,
    );
    // Unknown modifier bits stripped / rejected.
    expect(
      const PrivacyHotkey(modifiers: 0x10, keyCode: 0x50).isValid,
      isFalse,
    );
    expect(
      const PrivacyHotkey(modifiers: 0, keyCode: 0x50).sanitized(),
      PrivacyHotkey.defaultHotkey,
    );
    expect(
      const PrivacyHotkey(modifiers: 3, keyCode: 0x1B).sanitized(),
      PrivacyHotkey.defaultHotkey,
    );
    expect(
      const PrivacyHotkey(modifiers: 0x13, keyCode: 0x50).sanitized().modifiers,
      3,
    );
  });

  test('fromMap sanitizes dirty persisted values', () {
    final dirty = PrivacyHotkey.fromMap({'modifiers': 0, 'keyCode': 0x1B});
    expect(dirty.modifiers, PrivacyHotkey.defaultHotkey.modifiers);
    expect(dirty.keyCode, PrivacyHotkey.defaultHotkey.keyCode);
  });

  test('setHotkey / getHotkey round-trip', () async {
    expect(
      await PrivacyBlankDisplay.setHotkey(PrivacyHotkey.defaultHotkey),
      isTrue,
    );
    final hotkey = await PrivacyBlankDisplay.getHotkey();
    expect(hotkey.modifiers, 3);
    expect(hotkey.keyCode, 0x50);
    expect(hotkey.label, 'Ctrl+Alt+P');
  });
}
