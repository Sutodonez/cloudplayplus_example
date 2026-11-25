import 'dart:async';
import 'dart:ffi';
import 'dart:io';
import 'dart:isolate';
import 'dart:typed_data';

import 'package:ffi/ffi.dart';

import 'conpty_ffi.dart';
import 'shell_backend.dart';

/// Windows ConPTY-backed shell (CreatePseudoConsole + CreateProcessW).
///
/// Falls back is handled by the caller when [Platform.isWindows] is false or
/// ConPTY APIs are missing (pre-Win10 1809).
class ConPtyShellBackend implements ShellBackend {
  final String _kind;
  int _hPC = 0;
  int _hPipeWrite = 0; // we write input here
  int _hPipeRead = 0; // we read output here
  int _hProcess = 0;
  int _hThread = 0;
  Pointer<Void>? _attrList;
  StreamController<Uint8List>? _stdout;
  Completer<int>? _exit;
  Isolate? _reader;
  ReceivePort? _fromReader;
  SendPort? _toReader;
  bool _disposed = false;

  ConPtyShellBackend({String kind = 'conpty'}) : _kind = kind;

  @override
  String get kind => _kind;

  @override
  Stream<Uint8List> get stdout {
    final c = _stdout;
    if (c == null) throw StateError('ConPtyShellBackend not started');
    return c.stream;
  }

  /// True when kernel32 exports ConPTY entry points.
  static bool get isAvailable {
    if (!Platform.isWindows) return false;
    try {
      ConPtyFfi.ensureLoaded();
      return true;
    } catch (_) {
      return false;
    }
  }

  @override
  Future<void> start({
    required String shell,
    required List<String> args,
    required int cols,
    required int rows,
    String? workingDirectory,
    Map<String, String>? environment,
  }) async {
    if (!Platform.isWindows) {
      throw UnsupportedError('ConPTY requires Windows');
    }
    ConPtyFfi.ensureLoaded();
    _stdout = StreamController<Uint8List>.broadcast();
    _exit = Completer<int>();

    final hPipePTYIn = calloc<IntPtr>();
    final hPipeOut = calloc<IntPtr>();
    final hPipeIn = calloc<IntPtr>();
    final hPipePTYOut = calloc<IntPtr>();
    final hPC = calloc<IntPtr>();
    final sizePtr = calloc<IntPtr>();
    final pi = calloc<PROCESS_INFORMATION>();
    final si = calloc<STARTUPINFOEXW>();
    final hPCValue = calloc<IntPtr>();

    try {
      // Input pipe: we write to hPipeOut, ConPTY reads hPipePTYIn.
      if (ConPtyFfi.createPipe(hPipePTYIn, hPipeOut, nullptr, 0) == 0) {
        throw StateError('CreatePipe (input) failed');
      }
      // Output pipe: ConPTY writes hPipePTYOut, we read hPipeIn.
      if (ConPtyFfi.createPipe(hPipeIn, hPipePTYOut, nullptr, 0) == 0) {
        throw StateError('CreatePipe (output) failed');
      }

      final hr = ConPtyFfi.createPseudoConsole(
        packCoord(cols, rows),
        hPipePTYIn.value,
        hPipePTYOut.value,
        0,
        hPC,
      );
      if (hr != 0) {
        throw StateError(
          'CreatePseudoConsole failed HRESULT=0x${hr.toRadixString(16)}',
        );
      }
      _hPC = hPC.value;

      // Close ConPTY-owned pipe ends in this process after process create —
      // first prepare attribute list.
      sizePtr.value = 0;
      ConPtyFfi.initializeProcThreadAttributeList(
        nullptr,
        1,
        0,
        sizePtr,
      );
      _attrList = calloc<Uint8>(sizePtr.value).cast<Void>();
      if (ConPtyFfi.initializeProcThreadAttributeList(
            _attrList!,
            1,
            0,
            sizePtr,
          ) ==
          0) {
        throw StateError('InitializeProcThreadAttributeList failed');
      }

      hPCValue.value = _hPC;
      if (ConPtyFfi.updateProcThreadAttribute(
            _attrList!,
            0,
            ConPtyFfi.procThreadAttributePseudoConsole,
            hPCValue.cast<Void>(),
            sizeOf<IntPtr>(),
            nullptr,
            nullptr,
          ) ==
          0) {
        throw StateError('UpdateProcThreadAttribute failed');
      }

      si.ref.StartupInfo.cb = sizeOf<STARTUPINFOEXW>();
      si.ref.lpAttributeList = _attrList!;

      final cmd = _buildCommandLine(shell, args);
      final cmdPtr = cmd.toNativeUtf16();
      final cwdPtr = workingDirectory?.toNativeUtf16();

      final ok = ConPtyFfi.createProcessW(
        nullptr,
        cmdPtr,
        nullptr,
        nullptr,
        0, // bInheritHandles — ConPTY via attribute list
        ConPtyFfi.extendedStartupInfoPresent |
            ConPtyFfi.createUnicodeEnvironment,
        nullptr,
        cwdPtr ?? nullptr,
        si,
        pi,
      );
      calloc.free(cmdPtr);
      if (cwdPtr != null) calloc.free(cwdPtr);

      if (ok == 0) {
        throw StateError('CreateProcessW (ConPTY) failed');
      }

      _hProcess = pi.ref.hProcess;
      _hThread = pi.ref.hThread;
      _hPipeWrite = hPipeOut.value;
      _hPipeRead = hPipeIn.value;

      // Close sides owned by the pseudoconsole / child.
      ConPtyFfi.closeHandle(hPipePTYIn.value);
      ConPtyFfi.closeHandle(hPipePTYOut.value);

      await _startReader();
      // ignore: unawaited_futures
      _watchExit();
    } catch (e) {
      await dispose();
      rethrow;
    } finally {
      calloc.free(hPipePTYIn);
      calloc.free(hPipeOut);
      calloc.free(hPipeIn);
      calloc.free(hPipePTYOut);
      calloc.free(hPC);
      calloc.free(sizePtr);
      calloc.free(pi);
      calloc.free(si);
      calloc.free(hPCValue);
    }
  }

  Future<void> _startReader() async {
    _fromReader = ReceivePort();
    _reader = await Isolate.spawn(conPtyReadIsolate, _fromReader!.sendPort);
    final ready = Completer<SendPort>();
    _fromReader!.listen((msg) {
      if (msg is SendPort && !ready.isCompleted) {
        ready.complete(msg);
        return;
      }
      if (msg is List && msg.isNotEmpty) {
        final tag = msg[0] as String;
        if (tag == 'data' && msg.length > 1) {
          final bytes = Uint8List.fromList(List<int>.from(msg[1] as List));
          if (!(_stdout?.isClosed ?? true)) _stdout!.add(bytes);
        } else if (tag == 'eof' || tag == 'error') {
          if (!(_exit?.isCompleted ?? true)) {
            // Process may still be winding down; exit watcher sets code.
          }
        }
      }
    });
    _toReader = await ready.future;
    _toReader!.send(['read', _hPipeRead]);
  }

  Future<void> _watchExit() async {
    if (_hProcess == 0) return;
    await Future<void>.delayed(Duration.zero);
    // Poll so we do not block the isolate on WaitForSingleObject forever
    // without a way to cancel; 200ms is fine for session exit.
    while (!_disposed) {
      final code = calloc<Uint32>();
      try {
        ConPtyFfi.getExitCodeProcess(_hProcess, code);
        // STILL_ACTIVE = 259
        if (code.value != 259) {
          if (!(_exit?.isCompleted ?? true)) _exit!.complete(code.value);
          return;
        }
      } finally {
        calloc.free(code);
      }
      await Future<void>.delayed(const Duration(milliseconds: 200));
    }
  }

  static String _buildCommandLine(String shell, List<String> args) {
    final parts = <String>[_quoteWin(shell), ...args.map(_quoteWin)];
    return parts.join(' ');
  }

  static String _quoteWin(String s) {
    if (s.isEmpty) return '""';
    if (!s.contains(' ') && !s.contains('"')) return s;
    return '"${s.replaceAll('"', '\\"')}"';
  }

  @override
  void write(List<int> data) {
    if (_hPipeWrite == 0 || data.isEmpty) return;
    final buf = calloc<Uint8>(data.length);
    final written = calloc<Uint32>();
    try {
      buf.asTypedList(data.length).setAll(0, data);
      ConPtyFfi.writeFile(
        _hPipeWrite,
        buf,
        data.length,
        written,
        nullptr,
      );
    } finally {
      calloc.free(buf);
      calloc.free(written);
    }
  }

  @override
  void resize(int cols, int rows) {
    if (_hPC == 0) return;
    ConPtyFfi.resizePseudoConsole(_hPC, packCoord(cols, rows));
  }

  @override
  Future<void> kill() async {
    if (_hProcess != 0) {
      ConPtyFfi.terminateProcess(_hProcess, 1);
    }
    if (!(_exit?.isCompleted ?? true)) _exit!.complete(-1);
  }

  @override
  Future<int> get exitCode => _exit?.future ?? Future.value(-1);

  @override
  Future<void> dispose() async {
    if (_disposed) return;
    _disposed = true;
    _toReader?.send(['stop']);
    _fromReader?.close();
    _reader?.kill(priority: Isolate.immediate);
    await kill();
    if (_hPC != 0) {
      ConPtyFfi.closePseudoConsole(_hPC);
      _hPC = 0;
    }
    if (_attrList != null) {
      ConPtyFfi.deleteProcThreadAttributeList(_attrList!);
      calloc.free(_attrList!);
      _attrList = null;
    }
    if (_hPipeWrite != 0) {
      ConPtyFfi.closeHandle(_hPipeWrite);
      _hPipeWrite = 0;
    }
    if (_hPipeRead != 0) {
      ConPtyFfi.closeHandle(_hPipeRead);
      _hPipeRead = 0;
    }
    if (_hThread != 0) {
      ConPtyFfi.closeHandle(_hThread);
      _hThread = 0;
    }
    if (_hProcess != 0) {
      ConPtyFfi.closeHandle(_hProcess);
      _hProcess = 0;
    }
    await _stdout?.close();
    _stdout = null;
  }
}
