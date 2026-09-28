# T3SDK: the dinput8.dll loader (sdk/loader) plus example mods (sdk/mods),
# built as 32-bit DLLs for T3Main.exe against the vendored MinHook. Driven by
# tools/sdk.py, which configures and invokes this with Ninja; see docs/sdk.md.
cmake_minimum_required(VERSION 3.25)
project(T3SDK LANGUAGES C CXX)

if(NOT MSVC OR NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
  message(FATAL_ERROR
    "T3Main.exe is a 32-bit MSVC program: build with MSVC for x86 (tools/sdk.py sets that up).")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Static CRT: the DLLs need no Visual C++ redistributable in the game folder.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
add_compile_options(/utf-8)
add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX _CRT_SECURE_NO_WARNINGS)
add_link_options(/INCREMENTAL:NO)

# Everything that goes into the game's System/ folder is built into bin/.
set(T3SDK_BIN_DIR ${CMAKE_BINARY_DIR}/bin)

add_library(minhook STATIC
  third_party/minhook/src/buffer.c
  third_party/minhook/src/hook.c
  third_party/minhook/src/trampoline.c
  third_party/minhook/src/hde/hde32.c)
target_include_directories(minhook PUBLIC third_party/minhook/include)

# SDK headers plus the warning level for SDK code and mods.
add_library(t3sdk_headers INTERFACE)
target_include_directories(t3sdk_headers INTERFACE include)
target_compile_options(t3sdk_headers INTERFACE /W4)

add_subdirectory(loader)
add_subdirectory(mods/hello)

configure_file(T3SDK.ini ${T3SDK_BIN_DIR}/T3SDK.ini COPYONLY)
# The public headers go into bin/include/t3sdk/ too: bin/ is what the release
# zip holds, and mods (templates/mod) build against its include/. Deploy and
# the launcher's staging copy only DLL, PDB and INI files, so the headers
# never reach the game's System/ folder.
file(GLOB t3sdk_public_headers CONFIGURE_DEPENDS include/t3sdk/*.h include/t3sdk/*.hpp)
foreach(header IN LISTS t3sdk_public_headers)
  get_filename_component(header_name ${header} NAME)
  configure_file(${header} ${T3SDK_BIN_DIR}/include/t3sdk/${header_name} COPYONLY)
endforeach()
