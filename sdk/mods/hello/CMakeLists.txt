# Example mod target; see hello.cpp for the API walkthrough and
# sdk/CMakeLists.txt for how a mod gets registered here.
add_library(hello_mod SHARED hello.cpp)
target_link_libraries(hello_mod PRIVATE t3sdk_headers)
set_target_properties(hello_mod PROPERTIES
  OUTPUT_NAME hello
  RUNTIME_OUTPUT_DIRECTORY ${T3SDK_BIN_DIR}/mods)
