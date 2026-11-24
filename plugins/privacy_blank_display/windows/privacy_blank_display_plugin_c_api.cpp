#include "privacy_blank_display_plugin.h"
#include "include/privacy_blank_display/privacy_blank_display_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

void PrivacyBlankDisplayPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  privacy_blank_display::PrivacyBlankDisplayPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
