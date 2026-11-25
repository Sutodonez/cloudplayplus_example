import 'dart:async';
import 'dart:convert';
import 'dart:io';
import 'dart:typed_data';

import 'package:session_terminal_link/session_terminal_link.dart';
import 'package:test/test.dart';

void main() {
  test('host open + client receives state and echo output', () async {
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
      sendBinary: (b) async => host.onBinaryMessage(b),
    );

    final stateReady = Completer<TermSessionInfo>();
    final sub = client.sessionStates.listen((info) {
      if (info.state == TermSessionState.attached ||
          info.state == TermSessionState.ready) {
        if (!stateReady.isCompleted) stateReady.complete(info);
      }
    });

    final shell = Platform.isWindows
        ? 'powershell.exe'
        : (Platform.environment['SHELL'] ?? '/bin/bash');

    await client.open(name: 't1', shell: shell, cols: 80, rows: 24);
    final info = await stateReady.future.timeout(const Duration(seconds: 10));
    expect(info.sessionId, isNotEmpty);

    final outputDone = Completer<String>();
    final buf = StringBuffer();
    final outSub = client.output.listen((ev) {
      buf.write(utf8.decode(ev.bytes, allowMalformed: true));
      // Look for a unique marker we will echo.
      if (buf.toString().contains('CPP_TERM_OK') && !outputDone.isCompleted) {
        outputDone.complete(buf.toString());
      }
    });

    final echoCmd = Platform.isWindows
        ? 'Write-Output CPP_TERM_OK\r\n'
        : 'echo CPP_TERM_OK\n';
    await client.sendInput(info.sessionId, echoCmd);

    final text =
        await outputDone.future.timeout(const Duration(seconds: 15));
    expect(text, contains('CPP_TERM_OK'));

    await client.detach(info.sessionId);
    await client.kill(info.sessionId);

    await sub.cancel();
    await outSub.cancel();
    await host.dispose();
    await client.dispose();
  }, timeout: const Timeout(Duration(seconds: 45)));

  test('list returns host sessions to client', () async {
    late TerminalLinkEngine host;
    late TerminalLinkEngine client;

    host = TerminalLinkEngine(
      isHost: true,
      sendText: (t) async => client.onTextMessage(t),
      sendBinary: (b) async => client.onBinaryMessage(Uint8List.fromList(b)),
    );
    client = TerminalLinkEngine(
      isHost: false,
      sendText: (t) async => host.onTextMessage(t),
      sendBinary: (b) async {},
    );

    final listed = Completer<List<TermSessionInfo>>();
    final sub = client.sessionLists.listen((sessions) {
      if (sessions.isNotEmpty && !listed.isCompleted) {
        listed.complete(sessions);
      }
    });

    await client.open(name: 'listed');
    final sessions =
        await listed.future.timeout(const Duration(seconds: 10));
    expect(sessions.first.name, 'listed');

    await client.kill(sessions.first.sessionId);
    await sub.cancel();
    await host.dispose();
    await client.dispose();
  }, timeout: const Timeout(Duration(seconds: 30)));
}
