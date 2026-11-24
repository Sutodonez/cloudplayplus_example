import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'privacy_blank_display_method_channel.dart';

abstract class PrivacyBlankDisplayPlatform extends PlatformInterface {
  PrivacyBlankDisplayPlatform() : super(token: _token);

  static final Object _token = Object();

  static PrivacyBlankDisplayPlatform _instance =
      MethodChannelPrivacyBlankDisplay();

  static PrivacyBlankDisplayPlatform get instance => _instance;

  static set instance(PrivacyBlankDisplayPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<bool> isSupported() {
    throw UnimplementedError('isSupported() has not been implemented.');
  }

  Future<int> getMode() {
    throw UnimplementedError('getMode() has not been implemented.');
  }

  Future<bool> setMode(int modeIndex, {String? imagePath}) {
    throw UnimplementedError('setMode() has not been implemented.');
  }

  Future<void> setDismissLocksHost(bool enabled) {
    throw UnimplementedError('setDismissLocksHost() has not been implemented.');
  }

  Future<bool> lockWorkstation() {
    throw UnimplementedError('lockWorkstation() has not been implemented.');
  }

  Stream<void> get onDismissedByHotkey {
    throw UnimplementedError('onDismissedByHotkey has not been implemented.');
  }
}
