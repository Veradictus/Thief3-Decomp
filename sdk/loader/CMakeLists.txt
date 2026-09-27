# The dinput8.dll proxy/loader: the actual SDK, split into one .cpp/.hpp pair
# per concern (see each file's header comment). Built as t3sdk_loader and
# renamed to dinput8 below so it matches the real DLL it stands in for.
add_library(t3sdk_loader SHARED
  display.cpp
  dllmain.cpp
  engine.cpp
  executable_hash.cpp
  fixes.cpp
  iat.cpp
  log.cpp
  menu.cpp
  mods.cpp
  sdk.cpp
  dinput8.def)
target_link_libraries(t3sdk_loader PRIVATE minhook t3sdk_headers bcrypt)
set_target_properties(t3sdk_loader PROPERTIES
  OUTPUT_NAME dinput8
  RUNTIME_OUTPUT_DIRECTORY ${T3SDK_BIN_DIR})
