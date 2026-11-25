#include "privacy_blank_display_plugin.h"

#include <flutter/event_channel.h>
#include <flutter/event_stream_handler_functions.h>
#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#ifndef WDA_EXCLUDEFROMCAPTURE
#define WDA_EXCLUDEFROMCAPTURE 0x00000011
#endif

namespace privacy_blank_display {

namespace {

constexpr int kModeOff = 0;
constexpr int kModeBlankDisplay = 1;
constexpr int kModePrivacyScreen = 2;
constexpr int kHotkeyId = 0x50B1;

// Dart-side modifier bits (stable wire format).
constexpr int kModCtrlBit = 1;
constexpr int kModAltBit = 2;
constexpr int kModShiftBit = 4;
constexpr int kModWinBit = 8;

struct OverlayWindow {
  HWND hwnd = nullptr;
  HMONITOR monitor = nullptr;
};

std::mutex g_mutex;
int g_mode = kModeOff;
bool g_dismiss_locks = true;
bool g_hotkey_registered = false;
std::vector<OverlayWindow> g_overlays;
UINT_PTR g_blank_timer = 0;
flutter::PluginRegistrarWindows* g_registrar = nullptr;
std::unique_ptr<flutter::EventSink<flutter::EncodableValue>> g_event_sink;

// Default dismiss hotkey: Ctrl+Alt+P
int g_hotkey_mods = kModCtrlBit | kModAltBit;
UINT g_hotkey_vk = 'P';

// Host speaker mute while privacy is active; restore prior mute on exit.
bool g_mute_saved = false;
bool g_previous_mute = false;
bool g_privacy_muted = false;

// Marker so a crashed process can restore host unmute on next plugin load.
const wchar_t kMuteMarkerFile[] = L"cloudplayplus_privacy_mute.marker";

const wchar_t kOverlayClass[] = L"CpppPrivacyBlankOverlay";

std::wstring MuteMarkerPath() {
  wchar_t temp[MAX_PATH] = {};
  DWORD n = GetTempPathW(MAX_PATH, temp);
  if (n == 0 || n >= MAX_PATH) {
    return std::wstring(kMuteMarkerFile);
  }
  return std::wstring(temp) + kMuteMarkerFile;
}

void WriteMuteMarker() {
  HANDLE h = CreateFileW(MuteMarkerPath().c_str(), GENERIC_WRITE, 0, nullptr,
                         CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
  if (h != INVALID_HANDLE_VALUE) {
    CloseHandle(h);
  }
}

void ClearMuteMarker() {
  DeleteFileW(MuteMarkerPath().c_str());
}

bool MuteMarkerPresent() {
  DWORD attrs = GetFileAttributesW(MuteMarkerPath().c_str());
  return attrs != INVALID_FILE_ATTRIBUTES &&
         (attrs & FILE_ATTRIBUTE_DIRECTORY) == 0;
}

UINT DartModsToWinMods(int dart_mods) {
  UINT win = 0;
  if (dart_mods & kModCtrlBit) win |= MOD_CONTROL;
  if (dart_mods & kModAltBit) win |= MOD_ALT;
  if (dart_mods & kModShiftBit) win |= MOD_SHIFT;
  if (dart_mods & kModWinBit) win |= MOD_WIN;
  return win;
}

// Match settings UI: letter / digit / F1–F12 only.
bool IsAllowedHotkeyKey(int key) {
  return (key >= 0x30 && key <= 0x39) ||  // '0'..'9'
         (key >= 0x41 && key <= 0x5A) ||  // 'A'..'Z'
         (key >= 0x70 && key <= 0x7B);    // F1..F12
}

// Require at least one known modifier (Ctrl/Alt/Shift/Win).
bool IsAllowedHotkeyMods(int mods) {
  constexpr int kKnown =
      kModCtrlBit | kModAltBit | kModShiftBit | kModWinBit;
  return (mods & kKnown) != 0;
}

int SanitizeHotkeyMods(int mods) {
  constexpr int kKnown =
      kModCtrlBit | kModAltBit | kModShiftBit | kModWinBit;
  return mods & kKnown;
}

bool SetEndpointMute(bool mute, bool* out_previous) {
  HRESULT hr_init = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
  const bool need_uninit =
      SUCCEEDED(hr_init) || hr_init == S_FALSE || hr_init == RPC_E_CHANGED_MODE;

  IMMDeviceEnumerator* enumerator = nullptr;
  HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr,
                                CLSCTX_ALL, IID_PPV_ARGS(&enumerator));
  if (FAILED(hr) || enumerator == nullptr) {
    if (need_uninit && hr_init != RPC_E_CHANGED_MODE) CoUninitialize();
    return false;
  }

  IMMDevice* device = nullptr;
  hr = enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &device);
  enumerator->Release();
  if (FAILED(hr) || device == nullptr) {
    if (need_uninit && hr_init != RPC_E_CHANGED_MODE) CoUninitialize();
    return false;
  }

  IAudioEndpointVolume* volume = nullptr;
  hr = device->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr,
                        reinterpret_cast<void**>(&volume));
  device->Release();
  if (FAILED(hr) || volume == nullptr) {
    if (need_uninit && hr_init != RPC_E_CHANGED_MODE) CoUninitialize();
    return false;
  }

  if (out_previous != nullptr) {
    BOOL prev = FALSE;
    if (SUCCEEDED(volume->GetMute(&prev))) {
      *out_previous = prev != FALSE;
    }
  }

  hr = volume->SetMute(mute ? TRUE : FALSE, nullptr);
  volume->Release();
  if (need_uninit && hr_init != RPC_E_CHANGED_MODE) CoUninitialize();
  return SUCCEEDED(hr);
}

void ApplyHostMuteLocked(bool enable) {
  if (enable) {
    if (g_privacy_muted) return;
    bool previous = false;
    if (SetEndpointMute(true, &previous)) {
      g_previous_mute = previous;
      g_mute_saved = true;
      g_privacy_muted = true;
      WriteMuteMarker();
    }
  } else {
    if (!g_privacy_muted && !MuteMarkerPresent()) return;
    if (g_mute_saved) {
      SetEndpointMute(g_previous_mute, nullptr);
    } else {
      // Crash-recovery path: marker present but in-process state lost.
      SetEndpointMute(false, nullptr);
    }
    g_privacy_muted = false;
    g_mute_saved = false;
    ClearMuteMarker();
  }
}

/// If a previous process crashed while privacy-muted, restore unmute once.
void RecoverStaleMuteIfNeeded() {
  if (!MuteMarkerPresent()) return;
  SetEndpointMute(false, nullptr);
  ClearMuteMarker();
  g_privacy_muted = false;
  g_mute_saved = false;
}

LRESULT CALLBACK OverlayWndProc(HWND hwnd, UINT msg, WPARAM wparam,
                                LPARAM lparam) {
  switch (msg) {
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);
      RECT rc;
      GetClientRect(hwnd, &rc);
      HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
      FillRect(hdc, &rc, brush);
      DeleteObject(brush);
      EndPaint(hwnd, &ps);
      return 0;
    }
    case WM_ERASEBKGND:
      return 1;
    default:
      return DefWindowProc(hwnd, msg, wparam, lparam);
  }
}

void EnsureOverlayClass() {
  static bool registered = false;
  if (registered) {
    return;
  }
  WNDCLASSEXW wc = {};
  wc.cbSize = sizeof(wc);
  wc.lpfnWndProc = OverlayWndProc;
  wc.hInstance = GetModuleHandle(nullptr);
  wc.lpszClassName = kOverlayClass;
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  RegisterClassExW(&wc);
  registered = true;
}

void DestroyOverlaysLocked() {
  for (auto& o : g_overlays) {
    if (o.hwnd) {
      DestroyWindow(o.hwnd);
      o.hwnd = nullptr;
    }
  }
  g_overlays.clear();
}

BOOL CALLBACK MonitorEnumProc(HMONITOR monitor, HDC, LPRECT, LPARAM) {
  MONITORINFO mi = {};
  mi.cbSize = sizeof(mi);
  if (!GetMonitorInfo(monitor, &mi)) {
    return TRUE;
  }

  const RECT& r = mi.rcMonitor;
  HWND hwnd = CreateWindowExW(
      WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_LAYERED | WS_EX_NOACTIVATE,
      kOverlayClass, L"", WS_POPUP,
      r.left, r.top, r.right - r.left, r.bottom - r.top, nullptr, nullptr,
      GetModuleHandle(nullptr), nullptr);
  if (!hwnd) {
    return TRUE;
  }

  // Exclude overlay from desktop capture so the remote stream still sees the
  // real desktop (Win10 2004+). Fail closed if affinity cannot be set —
  // otherwise the overlay would blank the remote view as well.
  if (!SetWindowDisplayAffinity(hwnd, WDA_EXCLUDEFROMCAPTURE)) {
    DestroyWindow(hwnd);
    return TRUE;
  }
  SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
  ShowWindow(hwnd, SW_SHOWNOACTIVATE);
  SetWindowPos(hwnd, HWND_TOPMOST, r.left, r.top, r.right - r.left,
               r.bottom - r.top, SWP_NOACTIVATE | SWP_SHOWWINDOW);

  OverlayWindow ow;
  ow.hwnd = hwnd;
  ow.monitor = monitor;
  g_overlays.push_back(ow);
  return TRUE;
}

void CreateOverlaysLocked() {
  DestroyOverlaysLocked();
  EnsureOverlayClass();
  EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc, 0);
}

void StopBlankTimerLocked() {
  if (g_blank_timer != 0) {
    KillTimer(nullptr, g_blank_timer);
    g_blank_timer = 0;
  }
}

VOID CALLBACK BlankTimerProc(HWND, UINT, UINT_PTR, DWORD) {
  // Re-assert monitor power-off; user input may wake the panel.
  SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
}

void StartBlankTimerLocked() {
  StopBlankTimerLocked();
  g_blank_timer =
      SetTimer(nullptr, 0, 3000, BlankTimerProc);  // every 3s
}

void PowerOffMonitors() {
  SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);
}

void PowerOnMonitors() {
  // -1 = on
  SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)-1);
  // Nudge mouse to wake some drivers.
  mouse_event(MOUSEEVENTF_MOVE, 0, 1, 0, 0);
  mouse_event(MOUSEEVENTF_MOVE, 0, (DWORD)-1, 0, 0);
}

HWND RootHwnd() {
  if (g_registrar == nullptr || g_registrar->GetView() == nullptr) {
    return nullptr;
  }
  return GetAncestor(g_registrar->GetView()->GetNativeWindow(), GA_ROOT);
}

void UnregisterHotkeyLocked() {
  HWND hwnd = RootHwnd();
  if (g_hotkey_registered && hwnd != nullptr) {
    UnregisterHotKey(hwnd, kHotkeyId);
    g_hotkey_registered = false;
  }
}

bool RegisterHotkeyLocked() {
  if (g_hotkey_registered) {
    return true;
  }
  HWND hwnd = RootHwnd();
  if (hwnd == nullptr) {
    return false;
  }
  UINT win_mods = DartModsToWinMods(g_hotkey_mods);
  if (win_mods == 0 || g_hotkey_vk == 0) {
    return false;
  }
  if (RegisterHotKey(hwnd, kHotkeyId, win_mods, g_hotkey_vk)) {
    g_hotkey_registered = true;
    return true;
  }
  return false;
}

void EmitDismissed() {
  if (g_event_sink) {
    g_event_sink->Success(
        flutter::EncodableValue(std::string("dismissed")));
  }
}

bool ApplyModeLocked(int mode) {
  if (mode == g_mode) {
    return true;
  }

  // Tear down previous mode.
  if (g_mode == kModePrivacyScreen) {
    DestroyOverlaysLocked();
  }
  if (g_mode == kModeBlankDisplay) {
    StopBlankTimerLocked();
    PowerOnMonitors();
  }
  if (g_mode != kModeOff) {
    UnregisterHotkeyLocked();
    ApplyHostMuteLocked(false);
  }

  g_mode = mode;

  if (mode == kModeOff) {
    return true;
  }

  RegisterHotkeyLocked();
  ApplyHostMuteLocked(true);

  if (mode == kModePrivacyScreen) {
    CreateOverlaysLocked();
    if (g_overlays.empty()) {
      // Do not leave mute/hotkey engaged when overlay setup failed —
      // Dart `_active` stays previous/off while native would otherwise diverge.
      ApplyHostMuteLocked(false);
      UnregisterHotkeyLocked();
      g_mode = kModeOff;
      return false;
    }
    return true;
  }

  if (mode == kModeBlankDisplay) {
    // Physical panel power-off. Full UU-style "virtual screen carries desktop"
    // is orchestrated in Dart via hardware_simulator (VDD + primary-only).
    PowerOffMonitors();
    StartBlankTimerLocked();
    return true;
  }

  ApplyHostMuteLocked(false);
  UnregisterHotkeyLocked();
  g_mode = kModeOff;
  return false;
}

void DismissByHotkey() {
  std::lock_guard<std::mutex> lock(g_mutex);
  if (g_mode == kModeOff) {
    return;
  }
  ApplyModeLocked(kModeOff);
  const bool lock_host = g_dismiss_locks;
  EmitDismissed();
  if (lock_host) {
    LockWorkStation();
  }
}

int ReadIntArg(const flutter::EncodableMap* args, const char* key,
               int fallback) {
  if (args == nullptr) return fallback;
  auto it = args->find(flutter::EncodableValue(key));
  if (it == args->end()) return fallback;
  if (const auto* i = std::get_if<int32_t>(&it->second)) return *i;
  if (const auto* i64 = std::get_if<int64_t>(&it->second)) {
    return static_cast<int>(*i64);
  }
  return fallback;
}

}  // namespace

// static
void PrivacyBlankDisplayPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows* registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "privacy_blank_display",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<PrivacyBlankDisplayPlugin>(registrar);

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto& call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  auto event_channel =
      std::make_unique<flutter::EventChannel<flutter::EncodableValue>>(
          registrar->messenger(), "privacy_blank_display/events",
          &flutter::StandardMethodCodec::GetInstance());

  event_channel->SetStreamHandler(
      std::make_unique<flutter::StreamHandlerFunctions<flutter::EncodableValue>>(
          [](const flutter::EncodableValue*,
             std::unique_ptr<flutter::EventSink<flutter::EncodableValue>>&&
                 sink) {
            std::lock_guard<std::mutex> lock(g_mutex);
            g_event_sink = std::move(sink);
            return nullptr;
          },
          [](const flutter::EncodableValue*) {
            std::lock_guard<std::mutex> lock(g_mutex);
            g_event_sink.reset();
            return nullptr;
          }));

  registrar->AddPlugin(std::move(plugin));
}

PrivacyBlankDisplayPlugin::PrivacyBlankDisplayPlugin(
    flutter::PluginRegistrarWindows* registrar)
    : registrar_(registrar) {
  std::lock_guard<std::mutex> lock(g_mutex);
  g_registrar = registrar_;
  RecoverStaleMuteIfNeeded();
  window_proc_id_ = registrar_->RegisterTopLevelWindowProcDelegate(
      [](HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) -> std::optional<LRESULT> {
        if (message == WM_HOTKEY && static_cast<int>(wparam) == kHotkeyId) {
          DismissByHotkey();
          return 0;
        }
        if (message == WM_DISPLAYCHANGE) {
          std::lock_guard<std::mutex> lock(g_mutex);
          if (g_mode == kModePrivacyScreen) {
            CreateOverlaysLocked();
          }
        }
        return std::nullopt;
      });
}

PrivacyBlankDisplayPlugin::~PrivacyBlankDisplayPlugin() {
  std::lock_guard<std::mutex> lock(g_mutex);
  ApplyModeLocked(kModeOff);
  if (window_proc_id_ >= 0 && registrar_ != nullptr) {
    registrar_->UnregisterTopLevelWindowProcDelegate(window_proc_id_);
    window_proc_id_ = -1;
  }
  if (g_registrar == registrar_) {
    g_registrar = nullptr;
  }
}

void PrivacyBlankDisplayPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue>& method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  const auto& method = method_call.method_name();

  if (method == "isSupported") {
    result->Success(flutter::EncodableValue(true));
    return;
  }

  if (method == "getMode") {
    std::lock_guard<std::mutex> lock(g_mutex);
    result->Success(flutter::EncodableValue(g_mode));
    return;
  }

  if (method == "setDismissLocksHost") {
    const auto* args =
        std::get_if<flutter::EncodableMap>(method_call.arguments());
    bool enabled = true;
    if (args) {
      auto it = args->find(flutter::EncodableValue("enabled"));
      if (it != args->end()) {
        if (const auto* b = std::get_if<bool>(&it->second)) {
          enabled = *b;
        }
      }
    }
    std::lock_guard<std::mutex> lock(g_mutex);
    g_dismiss_locks = enabled;
    result->Success(nullptr);
    return;
  }

  if (method == "getHotkey") {
    std::lock_guard<std::mutex> lock(g_mutex);
    flutter::EncodableMap map;
    map[flutter::EncodableValue("modifiers")] =
        flutter::EncodableValue(g_hotkey_mods);
    map[flutter::EncodableValue("keyCode")] =
        flutter::EncodableValue(static_cast<int>(g_hotkey_vk));
    result->Success(flutter::EncodableValue(map));
    return;
  }

  if (method == "setHotkey") {
    const auto* args =
        std::get_if<flutter::EncodableMap>(method_call.arguments());
    const int mods_raw =
        ReadIntArg(args, "modifiers", kModCtrlBit | kModAltBit);
    const int key = ReadIntArg(args, "keyCode", static_cast<int>('P'));
    const int mods = SanitizeHotkeyMods(mods_raw);
    // Align with UI capture: known modifiers required; letter/digit/F only.
    if (!IsAllowedHotkeyMods(mods) || !IsAllowedHotkeyKey(key)) {
      result->Error("invalid_hotkey",
                    "hotkey must use Ctrl/Alt/Shift/Win plus letter/digit/F key");
      return;
    }
    bool ok = false;
    {
      std::lock_guard<std::mutex> lock(g_mutex);
      const bool was_registered = g_hotkey_registered;
      UnregisterHotkeyLocked();
      g_hotkey_mods = mods;
      g_hotkey_vk = static_cast<UINT>(key);
      if (was_registered || g_mode != kModeOff) {
        ok = RegisterHotkeyLocked();
      } else {
        ok = true;
      }
    }
    result->Success(flutter::EncodableValue(ok));
    return;
  }

  if (method == "lockWorkstation") {
    // Require explicit confirm arg so a stray invoke cannot lock the host.
    const auto* args =
        std::get_if<flutter::EncodableMap>(method_call.arguments());
    bool confirm = false;
    if (args) {
      auto it = args->find(flutter::EncodableValue("confirm"));
      if (it != args->end()) {
        if (const auto* b = std::get_if<bool>(&it->second)) {
          confirm = *b;
        }
      }
    }
    if (!confirm) {
      result->Error("confirm_required",
                    "lockWorkstation requires {confirm: true}");
      return;
    }
    result->Success(flutter::EncodableValue(LockWorkStation() != 0));
    return;
  }

  if (method == "setMode") {
    const auto* args =
        std::get_if<flutter::EncodableMap>(method_call.arguments());
    int mode = kModeOff;
    if (args) {
      auto it = args->find(flutter::EncodableValue("mode"));
      if (it != args->end()) {
        if (const auto* i = std::get_if<int32_t>(&it->second)) {
          mode = *i;
        } else if (const auto* i64 = std::get_if<int64_t>(&it->second)) {
          mode = static_cast<int>(*i64);
        } else {
          result->Error("invalid_mode", "mode must be int 0..2");
          return;
        }
      }
      // imagePath is reserved for a future custom screensaver; reject paths
      // until a whitelist loader exists (no path-injection surface today).
      if (args->find(flutter::EncodableValue("imagePath")) != args->end()) {
        result->Error("unsupported",
                      "imagePath is not implemented; omit the argument");
        return;
      }
    }
    if (mode < kModeOff || mode > kModePrivacyScreen) {
      result->Error("invalid_mode", "mode must be 0..2");
      return;
    }
    bool ok = false;
    {
      std::lock_guard<std::mutex> lock(g_mutex);
      ok = ApplyModeLocked(mode);
    }
    result->Success(flutter::EncodableValue(ok));
    return;
  }

  result->NotImplemented();
}

}  // namespace privacy_blank_display
