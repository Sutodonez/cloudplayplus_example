import 'dart:io';

import 'conpty_backend.dart';
import 'pipe_backend.dart';
import 'psmux.dart';
import 'shell_backend.dart';

/// Selects the best host shell backend for this platform.
///
/// Windows preference: **psmux session + ConPTY attach** → bare **ConPTY** →
/// pipe fallback. Non-Windows: pipe (POSIX PTY can be added later).
class ShellBackendFactory {
  /// Cached psmux detection for the process lifetime.
  static PsmuxCli? _psmux;
  static bool _psmuxChecked = false;

  static Future<PsmuxCli?> psmux() async {
    if (!_psmuxChecked) {
      _psmuxChecked = true;
      _psmux = await PsmuxCli.detect();
    }
    return _psmux;
  }

  /// Create a backend for a new interactive session.
  ///
  /// When [muxSessionName] is set and psmux is available, creates a detached
  /// psmux session and attaches via ConPTY (`psmux attach -t …`).
  static Future<ShellBackendChoice> create({
    required String shell,
    required List<String> shellArgs,
    required int cols,
    required int rows,
    String? muxSessionName,
    bool preferMux = true,
  }) async {
    if (Platform.isWindows) {
      final mux = preferMux ? await psmux() : null;
      if (mux != null && muxSessionName != null && muxSessionName.isNotEmpty) {
        await mux.newSession(
          name: muxSessionName,
          shell: shell,
          cols: cols,
          rows: rows,
        );
        if (ConPtyShellBackend.isAvailable) {
          final backend = ConPtyShellBackend(kind: 'psmux+conpty');
          final attach = mux.attachArgv(muxSessionName);
          await backend.start(
            shell: attach.first,
            args: attach.sublist(1),
            cols: cols,
            rows: rows,
            workingDirectory: Platform.environment['USERPROFILE'],
          );
          return ShellBackendChoice(
            backend: backend,
            kind: 'psmux+conpty',
            detail: 'psmux session=$muxSessionName via ConPTY attach',
          );
        }
        // psmux without ConPTY: pipe-attach (degraded TUI).
        final backend = PipeShellBackend();
        final attach = mux.attachArgv(muxSessionName);
        await backend.start(
          shell: attach.first,
          args: attach.sublist(1),
          cols: cols,
          rows: rows,
          workingDirectory: Platform.environment['USERPROFILE'],
        );
        return ShellBackendChoice(
          backend: backend,
          kind: 'psmux+pipe',
          detail: 'psmux session=$muxSessionName via pipe attach (no ConPTY)',
        );
      }

      if (ConPtyShellBackend.isAvailable) {
        final backend = ConPtyShellBackend();
        await backend.start(
          shell: shell,
          args: shellArgs,
          cols: cols,
          rows: rows,
          workingDirectory: Platform.environment['USERPROFILE'],
        );
        return ShellBackendChoice(
          backend: backend,
          kind: 'conpty',
          detail: 'CreatePseudoConsole + $shell',
        );
      }
    }

    final backend = PipeShellBackend();
    await backend.start(
      shell: shell,
      args: shellArgs,
      cols: cols,
      rows: rows,
      workingDirectory: Platform.environment['USERPROFILE'] ??
          Platform.environment['HOME'],
    );
    return ShellBackendChoice(
      backend: backend,
      kind: 'pipe',
      detail: Platform.isWindows
          ? 'pipe fallback (ConPTY/psmux unavailable)'
          : 'pipe Process on ${Platform.operatingSystem}',
    );
  }
}
