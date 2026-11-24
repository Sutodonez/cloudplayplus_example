/// Binary opcode for terminal I/O chunks on the reliable data channel.
/// Placed after CloudPlayPlus audio (65/66) and file-transfer (67) opcodes;
/// keep in sync with `lib/entities/messages.dart` (`LP_TERM_CHUNK`).
const int kTermChunkOpcode = 68;

/// JSON envelope root key for terminal control / meta messages.
const String kTermLinkJsonKey = 'term_link';

/// Control operations.
abstract final class TermLinkOp {
  static const String open = 'open';
  static const String attach = 'attach';
  static const String detach = 'detach';
  static const String kill = 'kill';
  static const String list = 'list';
  static const String listResult = 'list_result';
  static const String resize = 'resize';
  static const String input = 'input';
  static const String state = 'state';
  static const String error = 'error';
}

/// Lifecycle / readiness of a terminal session.
enum TermSessionState {
  starting,
  ready,
  attached,
  detached,
  exited,
  failed,
}

/// One session entry for list / state updates.
class TermSessionInfo {
  final String sessionId;
  final String name;
  final String shell;
  final TermSessionState state;
  final int cols;
  final int rows;
  final int? exitCode;
  final String? error;

  const TermSessionInfo({
    required this.sessionId,
    required this.name,
    required this.shell,
    required this.state,
    this.cols = 120,
    this.rows = 40,
    this.exitCode,
    this.error,
  });

  Map<String, dynamic> toJson() => {
        'sessionId': sessionId,
        'name': name,
        'shell': shell,
        'state': state.name,
        'cols': cols,
        'rows': rows,
        if (exitCode != null) 'exitCode': exitCode,
        if (error != null) 'error': error,
      };

  factory TermSessionInfo.fromJson(Map<String, dynamic> json) =>
      TermSessionInfo(
        sessionId: json['sessionId'] as String,
        name: json['name'] as String? ?? json['sessionId'] as String,
        shell: json['shell'] as String? ?? '',
        state: TermSessionState.values.firstWhere(
          (e) => e.name == (json['state'] as String? ?? 'ready'),
          orElse: () => TermSessionState.ready,
        ),
        cols: (json['cols'] as num?)?.toInt() ?? 120,
        rows: (json['rows'] as num?)?.toInt() ?? 40,
        exitCode: (json['exitCode'] as num?)?.toInt(),
        error: json['error'] as String?,
      );

  TermSessionInfo copyWith({
    String? sessionId,
    String? name,
    String? shell,
    TermSessionState? state,
    int? cols,
    int? rows,
    int? exitCode,
    String? error,
  }) =>
      TermSessionInfo(
        sessionId: sessionId ?? this.sessionId,
        name: name ?? this.name,
        shell: shell ?? this.shell,
        state: state ?? this.state,
        cols: cols ?? this.cols,
        rows: rows ?? this.rows,
        exitCode: exitCode ?? this.exitCode,
        error: error ?? this.error,
      );
}

/// Control message carried as `{"term_link": ...}` JSON text.
class TermLinkControl {
  final String op;
  final String? sessionId;
  final String? name;
  final String? shell;
  final int cols;
  final int rows;
  /// UTF-8 text input from controller (line or raw keystrokes).
  final String? data;
  final List<TermSessionInfo> sessions;
  final TermSessionState? state;
  final String? error;
  final int? exitCode;

  const TermLinkControl({
    required this.op,
    this.sessionId,
    this.name,
    this.shell,
    this.cols = 120,
    this.rows = 40,
    this.data,
    this.sessions = const [],
    this.state,
    this.error,
    this.exitCode,
  });

  Map<String, dynamic> toEnvelope() => {
        kTermLinkJsonKey: {
          'op': op,
          if (sessionId != null) 'sessionId': sessionId,
          if (name != null) 'name': name,
          if (shell != null) 'shell': shell,
          'cols': cols,
          'rows': rows,
          if (data != null) 'data': data,
          if (sessions.isNotEmpty)
            'sessions': sessions.map((e) => e.toJson()).toList(),
          if (state != null) 'state': state!.name,
          if (error != null) 'error': error,
          if (exitCode != null) 'exitCode': exitCode,
        },
      };

  factory TermLinkControl.fromEnvelope(Map<String, dynamic> envelope) {
    final body = envelope[kTermLinkJsonKey];
    if (body is! Map) {
      throw FormatException('missing $kTermLinkJsonKey');
    }
    final map = Map<String, dynamic>.from(body);
    final rawSessions = map['sessions'] as List? ?? const [];
    return TermLinkControl(
      op: map['op'] as String,
      sessionId: map['sessionId'] as String?,
      name: map['name'] as String?,
      shell: map['shell'] as String?,
      cols: (map['cols'] as num?)?.toInt() ?? 120,
      rows: (map['rows'] as num?)?.toInt() ?? 40,
      data: map['data'] as String?,
      sessions: rawSessions
          .map((e) =>
              TermSessionInfo.fromJson(Map<String, dynamic>.from(e as Map)))
          .toList(),
      state: map['state'] == null
          ? null
          : TermSessionState.values.firstWhere(
              (e) => e.name == map['state'],
              orElse: () => TermSessionState.ready,
            ),
      error: map['error'] as String?,
      exitCode: (map['exitCode'] as num?)?.toInt(),
    );
  }
}

/// Output event for controller UI.
class TerminalOutputEvent {
  final String sessionId;
  final List<int> bytes;
  final bool isStderr;

  const TerminalOutputEvent({
    required this.sessionId,
    required this.bytes,
    this.isStderr = false,
  });
}
