import 'dart:async';
import 'dart:typed_data';

import 'codec.dart';
import 'host_shell.dart';
import 'protocol.dart';

typedef TermSendText = Future<void> Function(String text);
typedef TermSendBinary = Future<void> Function(Uint8List bytes);

/// Peer-agnostic terminal linker over a reliable ordered side channel.
///
/// - [isHost] `true` on the controlled (server) side: owns shell processes.
/// - [isHost] `false` on the controller: opens/attaches UI sessions.
///
/// Control uses JSON `{"term_link":…}`; stdout/stderr use opcode
/// [kTermChunkOpcode]. Design mirrors UU public “终端连接” lifecycle
/// (open / attach / detach / kill / list) without NetEase binaries.
class TerminalLinkEngine {
  final TermSendText sendText;
  final TermSendBinary sendBinary;
  final bool isHost;

  final Map<String, HostShellSession> _hostSessions = {};
  final Map<int, String> _crcToSessionId = {};
  final List<TermSessionInfo> _remoteSessions = [];

  final _outputController = StreamController<TerminalOutputEvent>.broadcast();
  final _sessionsController =
      StreamController<List<TermSessionInfo>>.broadcast();
  final _stateController = StreamController<TermSessionInfo>.broadcast();

  String? activeSessionId;
  bool _disposed = false;

  TerminalLinkEngine({
    required this.sendText,
    required this.sendBinary,
    required this.isHost,
  });

  Stream<TerminalOutputEvent> get output => _outputController.stream;
  Stream<List<TermSessionInfo>> get sessionLists => _sessionsController.stream;
  Stream<TermSessionInfo> get sessionStates => _stateController.stream;

  List<TermSessionInfo> get knownSessions => isHost
      ? _hostSessions.values.map((s) => s.info).toList(growable: false)
      : List.unmodifiable(_remoteSessions);

  /// Controller: request a new host session (and attach immediately).
  Future<void> open({
    String? name,
    String? shell,
    int cols = 120,
    int rows = 40,
  }) async {
    _ensureAlive();
    if (isHost) {
      await _hostOpen(name: name, shell: shell, cols: cols, rows: rows);
      return;
    }
    await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
      op: TermLinkOp.open,
      name: name,
      shell: shell,
      cols: cols,
      rows: rows,
    )));
  }

  /// Controller: attach to an existing host session (replay ring buffer).
  Future<void> attach(String sessionId) async {
    _ensureAlive();
    activeSessionId = sessionId;
    if (isHost) {
      _hostSessions[sessionId]?.attach();
      return;
    }
    await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
      op: TermLinkOp.attach,
      sessionId: sessionId,
    )));
  }

  /// Controller: stop receiving output; host keeps the process alive.
  Future<void> detach(String sessionId) async {
    _ensureAlive();
    if (activeSessionId == sessionId) activeSessionId = null;
    if (isHost) {
      _hostSessions[sessionId]?.detach();
      return;
    }
    await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
      op: TermLinkOp.detach,
      sessionId: sessionId,
    )));
  }

  /// Kill (and remove) a session on the host.
  Future<void> kill(String sessionId) async {
    _ensureAlive();
    if (activeSessionId == sessionId) activeSessionId = null;
    if (isHost) {
      await _hostKill(sessionId);
      return;
    }
    await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
      op: TermLinkOp.kill,
      sessionId: sessionId,
    )));
  }

  /// Refresh the session list from the host.
  Future<void> list() async {
    _ensureAlive();
    if (isHost) {
      _emitHostList();
      return;
    }
    await sendText(TermLinkJsonCodec.encodeControl(
      const TermLinkControl(op: TermLinkOp.list),
    ));
  }

  Future<void> resize(String sessionId, int cols, int rows) async {
    _ensureAlive();
    if (isHost) {
      _hostSessions[sessionId]?.resize(cols, rows);
      return;
    }
    await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
      op: TermLinkOp.resize,
      sessionId: sessionId,
      cols: cols,
      rows: rows,
    )));
  }

  /// Send keystrokes / a command line to the attached session.
  Future<void> sendInput(String sessionId, String data) async {
    _ensureAlive();
    if (data.isEmpty) return;
    if (isHost) {
      _hostSessions[sessionId]?.writeInput(data);
      return;
    }
    await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
      op: TermLinkOp.input,
      sessionId: sessionId,
      data: data,
    )));
  }

  /// Split a psmux-backed session into another pane (Windows host).
  Future<void> splitPane(String sessionId, {bool vertical = true}) async {
    _ensureAlive();
    if (isHost) {
      await _hostSplit(sessionId, vertical: vertical);
      return;
    }
    await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
      op: TermLinkOp.splitPane,
      sessionId: sessionId,
      vertical: vertical,
    )));
  }

  /// Select a pane inside a psmux session.
  Future<void> selectPane(String sessionId, String paneId) async {
    _ensureAlive();
    if (isHost) {
      await _hostSessions[sessionId]?.selectPane(paneId);
      final s = _hostSessions[sessionId];
      if (s != null) await _sendState(s.info);
      return;
    }
    await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
      op: TermLinkOp.selectPane,
      sessionId: sessionId,
      paneId: paneId,
    )));
  }

  /// Ask the host to open a locally-visible Windows Terminal window.
  Future<void> visibleAttach(String sessionId) async {
    _ensureAlive();
    if (isHost) {
      await _hostVisibleAttach(sessionId);
      return;
    }
    await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
      op: TermLinkOp.visibleAttach,
      sessionId: sessionId,
    )));
  }

  void onTextMessage(String text) {
    final control = TermLinkJsonCodec.tryDecodeText(text);
    if (control == null) return;
    // ignore: discarded_futures
    _handleControl(control);
  }

  void onBinaryMessage(Uint8List bytes) {
    final chunk = TermChunkCodec.tryDecode(bytes);
    if (chunk == null) return;
    final sessionId = _crcToSessionId[chunk.sessionIdCrc32];
    if (sessionId == null && !isHost) {
      // Client may not know CRC yet — still emit with hex id hint.
      if (!_outputController.isClosed) {
        _outputController.add(TerminalOutputEvent(
          sessionId: activeSessionId ?? 'unknown',
          bytes: chunk.payload,
          isStderr: chunk.isStderr,
        ));
      }
      return;
    }
    final id = sessionId ?? activeSessionId;
    if (id == null) return;
    if (!_outputController.isClosed) {
      _outputController.add(TerminalOutputEvent(
        sessionId: id,
        bytes: chunk.payload,
        isStderr: chunk.isStderr,
      ));
    }
  }

  Future<void> _handleControl(TermLinkControl control) async {
    if (isHost) {
      switch (control.op) {
        case TermLinkOp.open:
          await _hostOpen(
            name: control.name,
            shell: control.shell,
            cols: control.cols,
            rows: control.rows,
          );
          break;
        case TermLinkOp.attach:
          if (control.sessionId != null) {
            final s = _hostSessions[control.sessionId!];
            s?.attach();
            if (s != null) await _sendState(s.info);
          }
          break;
        case TermLinkOp.detach:
          if (control.sessionId != null) {
            final s = _hostSessions[control.sessionId!];
            s?.detach();
            if (s != null) await _sendState(s.info);
          }
          break;
        case TermLinkOp.kill:
          if (control.sessionId != null) {
            await _hostKill(control.sessionId!);
          }
          break;
        case TermLinkOp.list:
          await _sendListResult();
          break;
        case TermLinkOp.resize:
          if (control.sessionId != null) {
            _hostSessions[control.sessionId!]
                ?.resize(control.cols, control.rows);
          }
          break;
        case TermLinkOp.input:
          if (control.sessionId != null && control.data != null) {
            _hostSessions[control.sessionId!]?.writeInput(control.data!);
          }
          break;
        case TermLinkOp.splitPane:
          if (control.sessionId != null) {
            try {
              await _hostSplit(
                control.sessionId!,
                vertical: control.vertical ?? true,
              );
            } catch (e) {
              await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
                op: TermLinkOp.error,
                sessionId: control.sessionId,
                error: e.toString(),
                state: TermSessionState.failed,
              )));
            }
          }
          break;
        case TermLinkOp.selectPane:
          if (control.sessionId != null && control.paneId != null) {
            try {
              await _hostSessions[control.sessionId!]
                  ?.selectPane(control.paneId!);
              final s = _hostSessions[control.sessionId!];
              if (s != null) await _sendState(s.info);
            } catch (e) {
              await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
                op: TermLinkOp.error,
                sessionId: control.sessionId,
                error: e.toString(),
                state: TermSessionState.failed,
              )));
            }
          }
          break;
        case TermLinkOp.visibleAttach:
          if (control.sessionId != null) {
            await _hostVisibleAttach(control.sessionId!);
          }
          break;
      }
      return;
    }

    // Client side
    switch (control.op) {
      case TermLinkOp.visibleAttachResult:
        if (!_stateController.isClosed) {
          _stateController.add(TermSessionInfo(
            sessionId: control.sessionId ?? activeSessionId ?? 'visible',
            name: control.name ?? 'visible_attach',
            shell: control.shell ?? '',
            state: (control.ok ?? false)
                ? TermSessionState.ready
                : TermSessionState.failed,
            error: control.ok == true ? null : control.detail,
            backend: control.detail,
          ));
        }
        break;
      case TermLinkOp.state:
        if (control.sessionId == null) return;
        final existed = _remoteSessions
            .any((s) => s.sessionId == control.sessionId);
        TermSessionInfo? prev;
        for (final s in _remoteSessions) {
          if (s.sessionId == control.sessionId) {
            prev = s;
            break;
          }
        }
        // Prefer wire fields; fall back to cached mux metadata so lifecycle
        // state updates never wipe backend / muxSession / panes.
        final panes = control.panes.isNotEmpty
            ? control.panes
            : (prev?.panes ?? const <String>[]);
        final info = TermSessionInfo(
          sessionId: control.sessionId!,
          name: control.name ?? prev?.name ?? control.sessionId!,
          shell: (control.shell != null && control.shell!.isNotEmpty)
              ? control.shell!
              : (prev?.shell ?? ''),
          state: control.state ?? prev?.state ?? TermSessionState.ready,
          cols: control.cols,
          rows: control.rows,
          exitCode: control.exitCode ?? prev?.exitCode,
          error: control.error ?? prev?.error,
          backend: control.backend ?? prev?.backend,
          muxSession: control.muxSession ?? prev?.muxSession,
          panes: panes,
        );
        _upsertRemote(info);
        _crcToSessionId[TermChunkCodec.sessionIdCrc32(info.sessionId)] =
            info.sessionId;
        // Focus only on open (new session), attach, or updates to the
        // already-active session — never let an unrelated ready/attached
        // steal activeSessionId.
        if (info.state == TermSessionState.ready ||
            info.state == TermSessionState.attached) {
          if (!existed ||
              activeSessionId == null ||
              activeSessionId == info.sessionId) {
            activeSessionId = info.sessionId;
          }
        }
        if (!_stateController.isClosed) _stateController.add(info);
        _emitRemoteList();
        break;
      case TermLinkOp.listResult:
        _remoteSessions
          ..clear()
          ..addAll(control.sessions);
        for (final s in control.sessions) {
          _crcToSessionId[TermChunkCodec.sessionIdCrc32(s.sessionId)] =
              s.sessionId;
        }
        _emitRemoteList();
        break;
      case TermLinkOp.error:
        if (!_stateController.isClosed) {
          _stateController.add(TermSessionInfo(
            sessionId: control.sessionId ?? 'error',
            name: control.name ?? 'error',
            shell: control.shell ?? '',
            state: TermSessionState.failed,
            error: control.error ?? 'unknown error',
          ));
        }
        break;
    }
  }

  Future<void> _hostOpen({
    String? name,
    String? shell,
    int cols = 120,
    int rows = 40,
  }) async {
    final id = newTerminalSessionId();
    final resolvedShell = (shell == null || shell.isEmpty)
        ? defaultHostShell()
        : shell;
    final sessionName =
        (name == null || name.isEmpty) ? 'session-$id' : name;
    final session = HostShellSession(
      sessionId: id,
      name: sessionName,
      shell: resolvedShell,
      cols: cols,
      rows: rows,
    );
    _hostSessions[id] = session;
    _crcToSessionId[TermChunkCodec.sessionIdCrc32(id)] = id;
    activeSessionId = id;

    session.output.listen((event) async {
      if (_disposed) return;
      await sendBinary(TermChunkCodec.encode(
        sessionId: event.sessionId,
        payload: event.bytes,
        isStderr: event.isStderr,
      ));
      // Also mirror locally for host-side debugging UIs.
      if (!_outputController.isClosed) _outputController.add(event);
    });
    session.stateChanges.listen((info) async {
      if (_disposed) return;
      if (!_stateController.isClosed) _stateController.add(info);
      await _sendState(info);
      _emitHostList();
    });

    try {
      await session.start();
      // start() already emits ready; ensure attach semantics for opener.
      session.attach();
      await _sendState(session.info);
      await _sendListResult();
    } catch (e) {
      await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
        op: TermLinkOp.error,
        sessionId: id,
        name: sessionName,
        shell: resolvedShell,
        error: e.toString(),
        state: TermSessionState.failed,
      )));
    }
  }

  Future<void> _hostKill(String sessionId) async {
    final s = _hostSessions.remove(sessionId);
    if (s == null) return;
    await s.dispose();
    await _sendState(TermSessionInfo(
      sessionId: sessionId,
      name: s.name,
      shell: s.shell,
      state: TermSessionState.exited,
      cols: s.cols,
      rows: s.rows,
      exitCode: s.info.exitCode,
      backend: s.backendKind,
      muxSession: s.muxSession,
    ));
    await _sendListResult();
    _emitHostList();
  }

  Future<void> _hostSplit(String sessionId, {bool vertical = true}) async {
    final s = _hostSessions[sessionId];
    if (s == null) return;
    await s.splitPane(vertical: vertical);
    await _sendState(s.info);
    await _sendListResult();
  }

  Future<void> _hostVisibleAttach(String sessionId) async {
    final s = _hostSessions[sessionId];
    if (s == null) {
      await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
        op: TermLinkOp.visibleAttachResult,
        sessionId: sessionId,
        ok: false,
        detail: 'session not found',
      )));
      return;
    }
    final result = await s.visibleAttach();
    await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
      op: TermLinkOp.visibleAttachResult,
      sessionId: sessionId,
      name: s.name,
      ok: result.ok,
      detail: result.detail,
    )));
  }

  Future<void> _sendState(TermSessionInfo info) async {
    await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
      op: TermLinkOp.state,
      sessionId: info.sessionId,
      name: info.name,
      shell: info.shell,
      cols: info.cols,
      rows: info.rows,
      state: info.state,
      error: info.error,
      exitCode: info.exitCode,
      backend: info.backend,
      muxSession: info.muxSession,
      panes: info.panes,
    )));
  }

  Future<void> _sendListResult() async {
    final sessions =
        _hostSessions.values.map((s) => s.info).toList(growable: false);
    await sendText(TermLinkJsonCodec.encodeControl(TermLinkControl(
      op: TermLinkOp.listResult,
      sessions: sessions,
    )));
  }

  void _emitHostList() {
    if (!_sessionsController.isClosed) {
      _sessionsController
          .add(_hostSessions.values.map((s) => s.info).toList());
    }
  }

  void _emitRemoteList() {
    if (!_sessionsController.isClosed) {
      _sessionsController.add(List.unmodifiable(_remoteSessions));
    }
  }

  void _upsertRemote(TermSessionInfo info) {
    final i = _remoteSessions.indexWhere((s) => s.sessionId == info.sessionId);
    if (i >= 0) {
      _remoteSessions[i] = info;
    } else {
      _remoteSessions.add(info);
    }
  }

  void _ensureAlive() {
    if (_disposed) {
      throw StateError('TerminalLinkEngine disposed');
    }
  }

  Future<void> dispose() async {
    if (_disposed) return;
    _disposed = true;
    for (final s in _hostSessions.values.toList()) {
      await s.dispose();
    }
    _hostSessions.clear();
    await _outputController.close();
    await _sessionsController.close();
    await _stateController.close();
  }
}
