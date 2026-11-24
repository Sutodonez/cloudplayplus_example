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
}
