// Host shell session API.
// IO implementation (ConPTY / psmux / pipes) when dart:io is available;
// Web/WASM gets a stub so controller builds avoid dart:ffi.
export 'host_shell_stub.dart'
    if (dart.library.io) 'host_shell_io.dart';
