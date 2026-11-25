import 'dart:async';
import 'dart:convert';

import 'package:session_terminal_link/session_terminal_link.dart';
import 'package:test/test.dart';

void main() {
  group('isValidTerminalPaneId', () {
    test('accepts tmux pane ids and bare indices', () {
      expect(isValidTerminalPaneId('%0'), isTrue);
      expect(isValidTerminalPaneId('%12'), isTrue);
      expect(isValidTerminalPaneId('0'), isTrue);
      expect(isValidTerminalPaneId('3'), isTrue);
    });

    test('rejects empty, overlong, and injection-shaped ids', () {
      expect(isValidTerminalPaneId(''), isFalse);
      expect(isValidTerminalPaneId('a' * (kMaxPaneIdLength + 1)), isFalse);
      expect(isValidTerminalPaneId('%0;kill'), isFalse);
      expect(isValidTerminalPaneId('sess:%0'), isFalse);
      expect(isValidTerminalPaneId('%0 %1'), isFalse);
      expect(isValidTerminalPaneId('../x'), isFalse);
    });

    test('requires membership when knownPanes is non-empty', () {
      expect(
        isValidTerminalPaneId('%0', knownPanes: const ['%0', '%1']),
        isTrue,
      );
      expect(
        isValidTerminalPaneId('%2', knownPanes: const ['%0', '%1']),
        isFalse,
      );
      expect(
        isValidTerminalPaneId('%0', knownPanes: const []),
        isTrue,
      );
    });
  });

  group('input / session caps', () {
    test('sendInput rejects oversized UTF-8 payloads on controller', () async {
      final engine = TerminalLinkEngine(
        isHost: false,
        sendText: (_) async {},
        sendBinary: (_) async {},
      );
      final huge = 'x' * (kMaxTerminalInputBytes + 1);
      expect(
        () => engine.sendInput('s1', huge),
        throwsA(isA<ArgumentError>()),
      );
      await engine.dispose();
    });

    test('host rejects oversized input with error control', () async {
      final errors = <TermLinkControl>[];
      late TerminalLinkEngine host;
      host = TerminalLinkEngine(
        isHost: true,
        sendText: (t) async {
          final c = TermLinkJsonCodec.tryDecodeText(t);
          if (c?.op == TermLinkOp.error) errors.add(c!);
        },
        sendBinary: (_) async {},
      );

      // Seed a fake host session slot via open failure path is heavy;
      // exercise the control handler input limit directly.
      host.onTextMessage(TermLinkJsonCodec.encodeControl(TermLinkControl(
        op: TermLinkOp.input,
        sessionId: 'missing',
        data: 'y' * (kMaxTerminalInputBytes + 8),
      )));

      await Future<void>.delayed(Duration.zero);
      expect(errors, isNotEmpty);
      expect(errors.first.error, contains('input exceeds'));
      await host.dispose();
    });

    test('host open refuses beyond kMaxHostTerminalSessions', () async {
      final errors = <String>[];
      late TerminalLinkEngine host;
      late TerminalLinkEngine client;

      host = TerminalLinkEngine(
        isHost: true,
        sendText: (t) async => client.onTextMessage(t),
        sendBinary: (b) async => client.onBinaryMessage(b),
      );
      client = TerminalLinkEngine(
        isHost: false,
        sendText: (t) async => host.onTextMessage(t),
        sendBinary: (_) async {},
      );

      final fail = Completer<String>();
      final sub = client.sessionStates.listen((info) {
        if (info.state == TermSessionState.failed &&
            (info.error ?? '').contains('session limit') &&
            !fail.isCompleted) {
          fail.complete(info.error!);
        }
      });

      // Fill to the cap with real sessions (pipe backend on Linux).
      final opened = <String>[];
      for (var i = 0; i < kMaxHostTerminalSessions; i++) {
        final ready = Completer<String>();
        late StreamSubscription<TermSessionInfo> once;
        once = client.sessionStates.listen((info) {
          if ((info.state == TermSessionState.ready ||
                  info.state == TermSessionState.attached) &&
              !ready.isCompleted) {
            ready.complete(info.sessionId);
            once.cancel();
          }
        });
        await client.open(name: 'cap-$i');
        opened.add(await ready.future.timeout(const Duration(seconds: 15)));
      }

      await client.open(name: 'over-cap');
      final err =
          await fail.future.timeout(const Duration(seconds: 10));
      errors.add(err);
      expect(errors.single, contains('session limit'));
      expect(host.knownSessions.length, kMaxHostTerminalSessions);

      for (final id in opened) {
        await client.kill(id);
      }
      await sub.cancel();
      await host.dispose();
      await client.dispose();
    }, timeout: const Timeout(Duration(seconds: 120)));
  });

  test('utf8 byte length matches cap boundary', () {
    final atLimit = utf8.decode(List.filled(kMaxTerminalInputBytes, 0x61));
    expect(utf8.encode(atLimit).length, kMaxTerminalInputBytes);
    final over = '$atLimit!';
    expect(utf8.encode(over).length, kMaxTerminalInputBytes + 1);
  });
}
