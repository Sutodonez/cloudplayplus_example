import 'dart:io';

/// Locates and drives the OSS [psmux](https://github.com/psmux/psmux)
/// multiplexer (tmux-compatible) on Windows. No NetEase `uuyc-mux` binary.
class PsmuxCli {
  final String executable;

  const PsmuxCli(this.executable);

  /// Search PATH (and common install dirs) for `psmux.exe` / `psmux`.
  static Future<PsmuxCli?> detect() async {
    if (!Platform.isWindows) return null;

    final pathEnv = Platform.environment['PATH'] ?? '';
    final sep = Platform.isWindows ? ';' : ':';
    final dirs = <String>[
      ...pathEnv.split(sep).where((d) => d.isNotEmpty),
      if (Platform.environment['LOCALAPPDATA'] != null)
        '${Platform.environment['LOCALAPPDATA']}\\Microsoft\\WinGet\\Links',
      if (Platform.environment['USERPROFILE'] != null)
        '${Platform.environment['USERPROFILE']}\\scoop\\shims',
      if (Platform.environment['USERPROFILE'] != null)
        '${Platform.environment['USERPROFILE']}\\.cargo\\bin',
      r'C:\Program Files\psmux',
    ];

    const names = ['psmux.exe', 'pmux.exe', 'psmux', 'pmux'];
    for (final dir in dirs) {
      for (final name in names) {
        final candidate = Directory(dir).uri.resolve(name).toFilePath();
        if (await File(candidate).exists()) {
          return PsmuxCli(candidate);
        }
      }
    }

    // Last resort: rely on PATH resolution via Process.
    try {
      final r = await Process.run('where', ['psmux'], runInShell: true);
      if (r.exitCode == 0) {
        final line = (r.stdout as String)
            .split(RegExp(r'\r?\n'))
            .map((s) => s.trim())
            .firstWhere((s) => s.isNotEmpty, orElse: () => '');
        if (line.isNotEmpty && await File(line).exists()) {
          return PsmuxCli(line);
        }
      }
    } catch (_) {}
    return null;
  }

  Future<ProcessResult> _run(List<String> args) =>
      Process.run(executable, args, runInShell: false);

  /// Create a detached named session (tmux-compatible).
  Future<void> newSession({
    required String name,
    String? shell,
    int cols = 120,
    int rows = 40,
  }) async {
    final args = <String>[
      'new-session',
      '-d',
      '-s',
      name,
      '-x',
      '$cols',
      '-y',
      '$rows',
    ];
    if (shell != null && shell.isNotEmpty) {
      args.addAll(['--', shell]);
    }
    final r = await _run(args);
    if (r.exitCode != 0) {
      throw StateError(
        'psmux new-session failed (${r.exitCode}): ${r.stderr}',
      );
    }
  }

  Future<void> killSession(String name) async {
    await _run(['kill-session', '-t', name]);
  }

  Future<bool> hasSession(String name) async {
    final r = await _run(['has-session', '-t', name]);
    return r.exitCode == 0;
  }

  /// Split the active window into another pane (`-h` / `-v`).
  Future<void> splitWindow({
    required String target,
    bool vertical = true,
    String? shell,
  }) async {
    final args = <String>[
      'split-window',
      vertical ? '-v' : '-h',
      '-t',
      target,
    ];
    if (shell != null && shell.isNotEmpty) {
      args.addAll(['--', shell]);
    }
    final r = await _run(args);
    if (r.exitCode != 0) {
      throw StateError(
        'psmux split-window failed (${r.exitCode}): ${r.stderr}',
      );
    }
  }

  Future<void> selectPane({
    required String target,
    required String pane,
  }) async {
    final r = await _run(['select-pane', '-t', '$target:$pane']);
    if (r.exitCode != 0) {
      // Fallback: treat [pane] as a raw tmux pane target.
      final r2 = await _run(['select-pane', '-t', pane]);
      if (r2.exitCode != 0) {
        throw StateError(
          'psmux select-pane failed (${r.exitCode}): ${r.stderr}',
        );
      }
    }
  }

  Future<List<String>> listPanes(String target) async {
    final r = await _run([
      'list-panes',
      '-t',
      target,
      '-F',
      '#{pane_id}',
    ]);
    if (r.exitCode != 0) return const [];
    return (r.stdout as String)
        .split(RegExp(r'\r?\n'))
        .map((s) => s.trim())
        .where((s) => s.isNotEmpty)
        .toList();
  }

  /// Command line to attach an existing session (for ConPTY / WT).
  List<String> attachArgv(String name) => [executable, 'attach', '-t', name];
}
