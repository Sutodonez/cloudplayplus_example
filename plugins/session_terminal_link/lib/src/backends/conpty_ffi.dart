import 'dart:ffi';
import 'dart:io';
import 'dart:isolate';

import 'package:ffi/ffi.dart';

/// Minimal Windows ConPTY + process bindings (kernel32).
///
/// Loaded only when [Platform.isWindows] is true at runtime. Compiles on
/// non-Windows; calling [ensureLoaded] elsewhere throws.
class ConPtyFfi {
  ConPtyFfi._();

  static DynamicLibrary? _k32;
  static bool _loaded = false;

  static late final _CreatePipeDart createPipe;
  static late final _CreatePseudoConsoleDart createPseudoConsole;
  static late final _ResizePseudoConsoleDart resizePseudoConsole;
  static late final _ClosePseudoConsoleDart closePseudoConsole;
  static late final _InitializeProcThreadAttributeListDart
      initializeProcThreadAttributeList;
  static late final _UpdateProcThreadAttributeDart updateProcThreadAttribute;
  static late final _DeleteProcThreadAttributeListDart
      deleteProcThreadAttributeList;
  static late final _CreateProcessWDart createProcessW;
  static late final _CloseHandleDart closeHandle;
  static late final _ReadFileDart readFile;
  static late final _WriteFileDart writeFile;
  static late final _TerminateProcessDart terminateProcess;
  static late final _WaitForSingleObjectDart waitForSingleObject;
  static late final _GetExitCodeProcessDart getExitCodeProcess;
  static late final _PeekNamedPipeDart peekNamedPipe;

  static const int procThreadAttributePseudoConsole = 0x00020016;
  static const int extendedStartupInfoPresent = 0x00080000;
  static const int createUnicodeEnvironment = 0x00000400;
  static const int infinite = 0xFFFFFFFF;

  static void ensureLoaded() {
    if (_loaded) return;
    if (!Platform.isWindows) {
      throw UnsupportedError('ConPTY FFI requires Windows');
    }
    _k32 = DynamicLibrary.open('kernel32.dll');
    createPipe = _k32!
        .lookupFunction<_CreatePipeNative, _CreatePipeDart>('CreatePipe');
    createPseudoConsole = _k32!.lookupFunction<_CreatePseudoConsoleNative,
        _CreatePseudoConsoleDart>('CreatePseudoConsole');
    resizePseudoConsole = _k32!.lookupFunction<_ResizePseudoConsoleNative,
        _ResizePseudoConsoleDart>('ResizePseudoConsole');
    closePseudoConsole = _k32!.lookupFunction<_ClosePseudoConsoleNative,
        _ClosePseudoConsoleDart>('ClosePseudoConsole');
    initializeProcThreadAttributeList = _k32!.lookupFunction<
        _InitializeProcThreadAttributeListNative,
        _InitializeProcThreadAttributeListDart>(
      'InitializeProcThreadAttributeList',
    );
    updateProcThreadAttribute = _k32!.lookupFunction<
        _UpdateProcThreadAttributeNative,
        _UpdateProcThreadAttributeDart>('UpdateProcThreadAttribute');
    deleteProcThreadAttributeList = _k32!.lookupFunction<
        _DeleteProcThreadAttributeListNative,
        _DeleteProcThreadAttributeListDart>('DeleteProcThreadAttributeList');
    createProcessW = _k32!
        .lookupFunction<_CreateProcessWNative, _CreateProcessWDart>(
            'CreateProcessW');
    closeHandle = _k32!
        .lookupFunction<_CloseHandleNative, _CloseHandleDart>('CloseHandle');
    readFile =
        _k32!.lookupFunction<_ReadFileNative, _ReadFileDart>('ReadFile');
    writeFile =
        _k32!.lookupFunction<_WriteFileNative, _WriteFileDart>('WriteFile');
    terminateProcess = _k32!.lookupFunction<_TerminateProcessNative,
        _TerminateProcessDart>('TerminateProcess');
    waitForSingleObject = _k32!.lookupFunction<_WaitForSingleObjectNative,
        _WaitForSingleObjectDart>('WaitForSingleObject');
    getExitCodeProcess = _k32!.lookupFunction<_GetExitCodeProcessNative,
        _GetExitCodeProcessDart>('GetExitCodeProcess');
    peekNamedPipe = _k32!
        .lookupFunction<_PeekNamedPipeNative, _PeekNamedPipeDart>(
            'PeekNamedPipe');
    _loaded = true;
  }
}

final class COORD extends Struct {
  @Int16()
  external int X;

  @Int16()
  external int Y;
}

final class SECURITY_ATTRIBUTES extends Struct {
  @Uint32()
  external int nLength;

  external Pointer<Void> lpSecurityDescriptor;

  @Int32()
  external int bInheritHandle;
}

final class STARTUPINFOW extends Struct {
  @Uint32()
  external int cb;
  external Pointer<Utf16> lpReserved;
  external Pointer<Utf16> lpDesktop;
  external Pointer<Utf16> lpTitle;
  @Uint32()
  external int dwX;
  @Uint32()
  external int dwY;
  @Uint32()
  external int dwXSize;
  @Uint32()
  external int dwYSize;
  @Uint32()
  external int dwXCountChars;
  @Uint32()
  external int dwYCountChars;
  @Uint32()
  external int dwFillAttribute;
  @Uint32()
  external int dwFlags;
  @Uint16()
  external int wShowWindow;
  @Uint16()
  external int cbReserved2;
  external Pointer<Uint8> lpReserved2;
  @IntPtr()
  external int hStdInput;
  @IntPtr()
  external int hStdOutput;
  @IntPtr()
  external int hStdError;
}

/// STARTUPINFOEXW = STARTUPINFOW + lpAttributeList.
final class STARTUPINFOEXW extends Struct {
  external STARTUPINFOW StartupInfo;
  external Pointer<Void> lpAttributeList;
}

final class PROCESS_INFORMATION extends Struct {
  @IntPtr()
  external int hProcess;
  @IntPtr()
  external int hThread;
  @Uint32()
  external int dwProcessId;
  @Uint32()
  external int dwThreadId;
}

typedef _CreatePipeNative = Int32 Function(
  Pointer<IntPtr> hReadPipe,
  Pointer<IntPtr> hWritePipe,
  Pointer<SECURITY_ATTRIBUTES> lpPipeAttributes,
  Uint32 nSize,
);
typedef _CreatePipeDart = int Function(
  Pointer<IntPtr> hReadPipe,
  Pointer<IntPtr> hWritePipe,
  Pointer<SECURITY_ATTRIBUTES> lpPipeAttributes,
  int nSize,
);

typedef _CreatePseudoConsoleNative = Int32 Function(
  Int32 sizePacked,
  IntPtr hInput,
  IntPtr hOutput,
  Uint32 dwFlags,
  Pointer<IntPtr> phPC,
);
typedef _CreatePseudoConsoleDart = int Function(
  int sizePacked,
  int hInput,
  int hOutput,
  int dwFlags,
  Pointer<IntPtr> phPC,
);

typedef _ResizePseudoConsoleNative = Int32 Function(
  IntPtr hPC,
  Int32 sizePacked,
);
typedef _ResizePseudoConsoleDart = int Function(int hPC, int sizePacked);

typedef _ClosePseudoConsoleNative = Void Function(IntPtr hPC);
typedef _ClosePseudoConsoleDart = void Function(int hPC);

typedef _InitializeProcThreadAttributeListNative = Int32 Function(
  Pointer<Void> lpAttributeList,
  Uint32 dwAttributeCount,
  Uint32 dwFlags,
  Pointer<IntPtr> lpSize,
);
typedef _InitializeProcThreadAttributeListDart = int Function(
  Pointer<Void> lpAttributeList,
  int dwAttributeCount,
  int dwFlags,
  Pointer<IntPtr> lpSize,
);

typedef _UpdateProcThreadAttributeNative = Int32 Function(
  Pointer<Void> lpAttributeList,
  Uint32 dwFlags,
  IntPtr Attribute,
  Pointer<Void> lpValue,
  IntPtr cbSize,
  Pointer<Void> lpPreviousValue,
  Pointer<IntPtr> lpReturnSize,
);
typedef _UpdateProcThreadAttributeDart = int Function(
  Pointer<Void> lpAttributeList,
  int dwFlags,
  int Attribute,
  Pointer<Void> lpValue,
  int cbSize,
  Pointer<Void> lpPreviousValue,
  Pointer<IntPtr> lpReturnSize,
);

typedef _DeleteProcThreadAttributeListNative = Void Function(
  Pointer<Void> lpAttributeList,
);
typedef _DeleteProcThreadAttributeListDart = void Function(
  Pointer<Void> lpAttributeList,
);

typedef _CreateProcessWNative = Int32 Function(
  Pointer<Utf16> lpApplicationName,
  Pointer<Utf16> lpCommandLine,
  Pointer<Void> lpProcessAttributes,
  Pointer<Void> lpThreadAttributes,
  Int32 bInheritHandles,
  Uint32 dwCreationFlags,
  Pointer<Void> lpEnvironment,
  Pointer<Utf16> lpCurrentDirectory,
  Pointer<STARTUPINFOEXW> lpStartupInfo,
  Pointer<PROCESS_INFORMATION> lpProcessInformation,
);
typedef _CreateProcessWDart = int Function(
  Pointer<Utf16> lpApplicationName,
  Pointer<Utf16> lpCommandLine,
  Pointer<Void> lpProcessAttributes,
  Pointer<Void> lpThreadAttributes,
  int bInheritHandles,
  int dwCreationFlags,
  Pointer<Void> lpEnvironment,
  Pointer<Utf16> lpCurrentDirectory,
  Pointer<STARTUPINFOEXW> lpStartupInfo,
  Pointer<PROCESS_INFORMATION> lpProcessInformation,
);

typedef _CloseHandleNative = Int32 Function(IntPtr hObject);
typedef _CloseHandleDart = int Function(int hObject);

typedef _ReadFileNative = Int32 Function(
  IntPtr hFile,
  Pointer<Uint8> lpBuffer,
  Uint32 nNumberOfBytesToRead,
  Pointer<Uint32> lpNumberOfBytesRead,
  Pointer<Void> lpOverlapped,
);
typedef _ReadFileDart = int Function(
  int hFile,
  Pointer<Uint8> lpBuffer,
  int nNumberOfBytesToRead,
  Pointer<Uint32> lpNumberOfBytesRead,
  Pointer<Void> lpOverlapped,
);

typedef _WriteFileNative = Int32 Function(
  IntPtr hFile,
  Pointer<Uint8> lpBuffer,
  Uint32 nNumberOfBytesToWrite,
  Pointer<Uint32> lpNumberOfBytesWritten,
  Pointer<Void> lpOverlapped,
);
typedef _WriteFileDart = int Function(
  int hFile,
  Pointer<Uint8> lpBuffer,
  int nNumberOfBytesToWrite,
  Pointer<Uint32> lpNumberOfBytesWritten,
  Pointer<Void> lpOverlapped,
);

typedef _TerminateProcessNative = Int32 Function(
  IntPtr hProcess,
  Uint32 uExitCode,
);
typedef _TerminateProcessDart = int Function(int hProcess, int uExitCode);

typedef _WaitForSingleObjectNative = Uint32 Function(
  IntPtr hHandle,
  Uint32 dwMilliseconds,
);
typedef _WaitForSingleObjectDart = int Function(
  int hHandle,
  int dwMilliseconds,
);

typedef _GetExitCodeProcessNative = Int32 Function(
  IntPtr hProcess,
  Pointer<Uint32> lpExitCode,
);
typedef _GetExitCodeProcessDart = int Function(
  int hProcess,
  Pointer<Uint32> lpExitCode,
);

typedef _PeekNamedPipeNative = Int32 Function(
  IntPtr hNamedPipe,
  Pointer<Void> lpBuffer,
  Uint32 nBufferSize,
  Pointer<Uint32> lpBytesRead,
  Pointer<Uint32> lpTotalBytesAvail,
  Pointer<Uint32> lpBytesLeftThisMessage,
);
typedef _PeekNamedPipeDart = int Function(
  int hNamedPipe,
  Pointer<Void> lpBuffer,
  int nBufferSize,
  Pointer<Uint32> lpBytesRead,
  Pointer<Uint32> lpTotalBytesAvail,
  Pointer<Uint32> lpBytesLeftThisMessage,
);

/// Pack COORD as a 32-bit value (X low 16, Y high 16) for ConPTY APIs that
/// take COORD by value under stdcall.
int packCoord(int cols, int rows) =>
    (cols & 0xffff) | ((rows & 0xffff) << 16);

/// Blocking reader isolate entry — keeps ConPTY output pipe serviced.
void conPtyReadIsolate(SendPort sendPort) {
  final replyPort = ReceivePort();
  sendPort.send(replyPort.sendPort);
  replyPort.listen((message) {
    if (message is! List || message.length < 2) return;
    final cmd = message[0] as String;
    if (cmd == 'read') {
      final hRead = message[1] as int;
      try {
        ConPtyFfi.ensureLoaded();
        final buf = calloc<Uint8>(4096);
        final read = calloc<Uint32>();
        try {
          while (true) {
            final ok = ConPtyFfi.readFile(
              hRead,
              buf,
              4096,
              read,
              nullptr,
            );
            if (ok == 0) {
              sendPort.send(['eof', null]);
              break;
            }
            final n = read.value;
            if (n == 0) {
              sendPort.send(['eof', null]);
              break;
            }
            sendPort.send(['data', buf.asTypedList(n).toList()]);
          }
        } finally {
          calloc.free(buf);
          calloc.free(read);
        }
      } catch (e) {
        sendPort.send(['error', e.toString()]);
      }
    } else if (cmd == 'stop') {
      replyPort.close();
      Isolate.current.kill(priority: Isolate.immediate);
    }
  });
}
