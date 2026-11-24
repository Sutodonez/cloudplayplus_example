#include "privacy_blank_display_plugin.h"

#include <flutter/event_channel.h>
#include <flutter/event_stream_handler_functions.h>
#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <windows.h>

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
constexpr int kHotkeyId = 0x50B1;  // Ctrl+Alt+P

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

const wchar_t kOverlayClass[] = L"CpppPrivacyBlankOverlay";

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
  // real desktop (Win10 2004+). Older builds ignore the call.
  SetWindowDisplayAffinity(hwnd, WDA_EXCLUDEFROMCAPTURE);
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
  if (g_blank_timer != 0 && g_registrar != nullptr) {
    KillTimer(nullptr, g_blank_timer);
    // Prefer registrar HWND timer if available; KillTimer with nullptr id is
    // best-effort for the SetTimer path below.
  }
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

void RegisterHotkeyLocked() {
  if (g_hotkey_registered) {
    return;
  }
  HWND hwnd = RootHwnd();
  if (hwnd == nullptr) {
    return;
  }
  if (RegisterHotKey(hwnd, kHotkeyId, MOD_CONTROL | MOD_ALT, 'P')) {
    g_hotkey_registered = true;
  }
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
  }

  g_mode = mode;

  if (mode == kModeOff) {
    return true;
  }

  RegisterHotkeyLocked();

  if (mode == kModePrivacyScreen) {
    CreateOverlaysLocked();
    return !g_overlays.empty();
  }

  if (mode == kModeBlankDisplay) {
    // Physical panel power-off. Full UU-style "virtual screen carries desktop"
    // is orchestrated in Dart via hardware_simulator (VDD + primary-only).
    PowerOffMonitors();
    StartBlankTimerLocked();
    return true;
  }

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

  if (method == "lockWorkstation") {
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
        }
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
