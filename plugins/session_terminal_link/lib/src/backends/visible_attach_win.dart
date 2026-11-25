import 'dart:convert';
import 'dart:io';

/// Locally-visible Windows Terminal attach for a host terminal session.
///
/// Mirrors the GameViewer “visible mux attach” product shape using **OSS**
/// pieces only: locate `wt.exe` / Windows Terminal `settings.json`, then
/// launch a WT tab that runs `psmux attach -t <session>` (or a shell
/// command line). Never copies NetEase helpers.
class WindowsTerminalVisibleAttach {
  /// Result of a visible-attach attempt.
  final bool ok;
  final String detail;
  final int? pid;

  const WindowsTerminalVisibleAttach({
    required this.ok,
    required this.detail,
    this.pid,
  });

  /// Find `wt.exe` on a typical Windows install.
  static Future<String?> findWtExe() async {
    if (!Platform.isWindows) return null;

    final candidates = <String>[
      // App execution alias / PATH
      'wt.exe',
      if (Platform.environment['LOCALAPPDATA'] != null)
        '${Platform.environment['LOCALAPPDATA']}\\Microsoft\\WindowsApps\\wt.exe',
      r'C:\Program Files\Windows Terminal\wt.exe',
      r'C:\Program Files (x86)\Windows Terminal\wt.exe',
    ];
    for (final c in candidates) {
      if (c == 'wt.exe') {
        try {
          final r = await Process.run('where', ['wt'], runInShell: true);
          if (r.exitCode == 0) {
            final line = (r.stdout as String)
                .split(RegExp(r'\r?\n'))
                .map((s) => s.trim())
                .firstWhere((s) => s.toLowerCase().endsWith('wt.exe'),
                    orElse: () => '');
            if (line.isNotEmpty) return line;
          }
        } catch (_) {}
        continue;
      }
      if (await File(c).exists()) return c;
    }
    return null;
  }

  /// Packages path for stable Windows Terminal settings.json (if present).
  static Future<File?> findSettingsJson() async {
    if (!Platform.isWindows) return null;
    final local = Platform.environment['LOCALAPPDATA'];
    if (local == null) return null;
    final paths = [
      '$local\\Packages\\Microsoft.WindowsTerminal_8wekyb3d8bbwe\\LocalState\\settings.json',
      '$local\\Packages\\Microsoft.WindowsTerminalPreview_8wekyb3d8bbwe\\LocalState\\settings.json',
    ];
    for (final p in paths) {
      final f = File(p);
      if (await f.exists()) return f;
    }
    return null;
  }

  /// Launch Windows Terminal attached to a psmux session or arbitrary command.
  ///
  /// Prefer [psmuxAttachSession]: `wt.exe -w 0 nt -- psmux attach -t <name>`.
  static Future<WindowsTerminalVisibleAttach> attach({
    String? psmuxExe,
    String? psmuxAttachSession,
    String? commandLine,
    String? displayName,
  }) async {
    if (!Platform.isWindows) {
      return const WindowsTerminalVisibleAttach(
        ok: false,
        detail: 'visible attach requires Windows host',
      );
    }
    final wt = await findWtExe();
    if (wt == null) {
      return const WindowsTerminalVisibleAttach(
        ok: false,
        detail: 'Windows Terminal (wt.exe) not found',
      );
    }

    final List<String> argv;
    if (psmuxAttachSession != null && psmuxAttachSession.isNotEmpty) {
      final mux = psmuxExe ?? 'psmux';
      argv = [
        wt,
        '-w',
        '0',
        'nt',
        '--title',
        displayName ?? 'cppp:$psmuxAttachSession',
        '--',
        mux,
        'attach',
        '-t',
        psmuxAttachSession,
      ];
    } else if (commandLine != null && commandLine.isNotEmpty) {
      argv = [
        wt,
        '-w',
        '0',
        'nt',
        '--title',
        displayName ?? 'cppp-terminal',
        'cmd',
        '/c',
        commandLine,
      ];
    } else {
      return const WindowsTerminalVisibleAttach(
        ok: false,
        detail: 'need psmuxAttachSession or commandLine',
      );
    }

    try {
      final proc = await Process.start(
        argv.first,
        argv.sublist(1),
        mode: ProcessStartMode.detached,
      );
      return WindowsTerminalVisibleAttach(
        ok: true,
        detail: 'launched Windows Terminal pid=${proc.pid}',
        pid: proc.pid,
      );
    } catch (e) {
      return WindowsTerminalVisibleAttach(
        ok: false,
        detail: 'failed to launch wt: $e',
      );
    }
  }

  /// Optionally ensure a named profile exists in settings.json (best-effort).
  /// Does not throw — attach() does not require this.
  static Future<void> ensureProfile({
    required String profileName,
    required String commandLine,
  }) async {
    final settings = await findSettingsJson();
    if (settings == null) return;
    try {
      final raw = await settings.readAsString();
      final map = jsonDecode(raw);
      if (map is! Map) return;
      final list = map['profiles'];
      Map<String, dynamic> profilesRoot;
      List<dynamic> profileList;
      if (list is Map) {
        profilesRoot = Map<String, dynamic>.from(list);
        profileList = List<dynamic>.from(profilesRoot['list'] as List? ?? []);
      } else if (list is List) {
        profilesRoot = {};
        profileList = List<dynamic>.from(list);
      } else {
        return;
      }
      final exists = profileList.any(
        (p) => p is Map && (p['name'] as String?) == profileName,
      );
      if (!exists) {
        profileList.add({
          'name': profileName,
          'commandline': commandLine,
          'hidden': false,
        });
        if (list is Map) {
          profilesRoot['list'] = profileList;
          map['profiles'] = profilesRoot;
        } else {
          map['profiles'] = profileList;
        }
        await settings.writeAsString(
          const JsonEncoder.withIndent('  ').convert(map),
        );
      }
    } catch (_) {
      // Best-effort only; launch path does not depend on profile injection.
    }
  }
}
