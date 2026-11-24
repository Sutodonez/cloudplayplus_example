import 'dart:async';

import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'privacy_blank_display_platform_interface.dart';

const String _channelName = 'privacy_blank_display';
const String _eventChannelName = 'privacy_blank_display/events';

class MethodChannelPrivacyBlankDisplay extends PrivacyBlankDisplayPlatform {
  @visibleForTesting
  final MethodChannel methodChannel = const MethodChannel(_channelName);

  @visibleForTesting
  final EventChannel eventChannel = const EventChannel(_eventChannelName);

  StreamController<void>? _dismissController;
  StreamSubscription<dynamic>? _eventSub;

  @override
  Future<bool> isSupported() async {
    if (kIsWeb) return false;
    if (defaultTargetPlatform != TargetPlatform.windows) return false;
    final result = await methodChannel.invokeMethod<bool>('isSupported');
    return result ?? false;
  }

  @override
  Future<int> getMode() async {
    if (kIsWeb || defaultTargetPlatform != TargetPlatform.windows) {
      return 0;
    }
    final result = await methodChannel.invokeMethod<int>('getMode');
    return result ?? 0;
  }

  @override
  Future<bool> setMode(int modeIndex, {String? imagePath}) async {
    if (kIsWeb || defaultTargetPlatform != TargetPlatform.windows) {
      return false;
    }
    final result = await methodChannel.invokeMethod<bool>('setMode', {
      'mode': modeIndex,
      if (imagePath != null) 'imagePath': imagePath,
    });
    return result ?? false;
  }

  @override
  Future<void> setDismissLocksHost(bool enabled) async {
    if (kIsWeb || defaultTargetPlatform != TargetPlatform.windows) {
      return;
    }
    await methodChannel.invokeMethod<void>('setDismissLocksHost', {
      'enabled': enabled,
    });
  }

  @override
  Future<bool> lockWorkstation() async {
    if (kIsWeb || defaultTargetPlatform != TargetPlatform.windows) {
      return false;
    }
    final result = await methodChannel.invokeMethod<bool>('lockWorkstation');
    return result ?? false;
  }

  @override
  Stream<void> get onDismissedByHotkey {
    _dismissController ??= StreamController<void>.broadcast(
      onListen: _ensureEventSubscription,
      onCancel: () {
        if (_dismissController?.hasListener == false) {
          _eventSub?.cancel();
          _eventSub = null;
        }
      },
    );
    return _dismissController!.stream;
  }

  void _ensureEventSubscription() {
    if (_eventSub != null) return;
    if (kIsWeb || defaultTargetPlatform != TargetPlatform.windows) return;
    _eventSub = eventChannel.receiveBroadcastStream().listen((event) {
      if (event == 'dismissed') {
        _dismissController?.add(null);
      }
    });
  }
}
