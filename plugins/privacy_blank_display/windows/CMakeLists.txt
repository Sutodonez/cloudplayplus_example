cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME "privacy_blank_display")
project(${PROJECT_NAME} LANGUAGES CXX)

set(PLUGIN_NAME "privacy_blank_display_plugin")

list(APPEND PLUGIN_SOURCES
  "privacy_blank_display_plugin.cpp"
  "privacy_blank_display_plugin.h"
)

add_library(${PLUGIN_NAME} SHARED
  "include/privacy_blank_display/privacy_blank_display_plugin_c_api.h"
  "privacy_blank_display_plugin_c_api.cpp"
  ${PLUGIN_SOURCES}
)

apply_standard_settings(${PLUGIN_NAME})

set_target_properties(${PLUGIN_NAME} PROPERTIES
  CXX_VISIBILITY_PRESET hidden)
target_compile_definitions(${PLUGIN_NAME} PRIVATE FLUTTER_PLUGIN_IMPL)

target_include_directories(${PLUGIN_NAME} INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PLUGIN_NAME} PRIVATE flutter flutter_wrapper_plugin)

# User32 for monitor / hotkey / overlay windows.
target_link_libraries(${PLUGIN_NAME} PRIVATE user32 gdi32)

set(privacy_blank_display_bundled_libraries
  ""
  PARENT_SCOPE
)
