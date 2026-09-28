# A T3SDK mod: builds <id>.dll against the SDK headers, writes mod.json from
# mod.json.in, and packs <id>-<version>.t3mod with the `package` target.
# README.md explains the steps; the package format is docs/mods.md in T3SDK.
cmake_minimum_required(VERSION 3.25)

# The only place the mod's version is set: mod.json, the package's name and
# the release tag (vX.Y.Z) all follow it.
project(my_mod VERSION 0.1.0 LANGUAGES CXX)

# The mod's id: its permanent name, install folder, DLL and package name.
# 1-64 characters of a-z, 0-9, '_' and '-'.
set(MOD_ID "my-mod")

if(NOT MSVC OR NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
  message(FATAL_ERROR
    "T3Main.exe is a 32-bit MSVC program: build with MSVC for x86 (an x86 developer prompt, or the presets).")
endif()
string(LENGTH "${MOD_ID}" mod_id_length)
if(NOT MOD_ID MATCHES "^[a-z0-9][a-z0-9_-]*$" OR mod_id_length GREATER 64)
  message(FATAL_ERROR "MOD_ID \"${MOD_ID}\": use 1-64 characters of a-z, 0-9, '_' and '-'.")
endif()

# The SDK headers: a folder holding t3sdk/t3sdk.h, such as a T3SDK checkout's
# sdk/include. Left empty, they come from the T3SDK release T3SDK_VERSION.
set(T3SDK_INCLUDE_DIR "" CACHE PATH "Folder holding t3sdk/t3sdk.h (empty: download the SDK release)")
set(T3SDK_VERSION "0.2.0" CACHE STRING "T3SDK release to download the headers from")
if(T3SDK_INCLUDE_DIR)
  file(TO_CMAKE_PATH "${T3SDK_INCLUDE_DIR}" t3sdk_include)
else()
  include(FetchContent)
  FetchContent_Declare(t3sdk
    URL "https://github.com/Veradictus/Thief3-Decomp/releases/download/v${T3SDK_VERSION}/T3SDK_${T3SDK_VERSION}_x86.zip"
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
  FetchContent_MakeAvailable(t3sdk)
  set(t3sdk_include "${t3sdk_SOURCE_DIR}/include")
endif()
if(NOT EXISTS "${t3sdk_include}/t3sdk/t3sdk.h")
  message(FATAL_ERROR "No t3sdk/t3sdk.h in ${t3sdk_include}: set T3SDK_INCLUDE_DIR to the SDK's include "
    "folder, or T3SDK_VERSION to a release whose zip has include/.")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Static CRT: the DLL needs no Visual C++ redistributable on the player's machine.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_library(mod SHARED src/mod.cpp)
target_include_directories(mod PRIVATE "${t3sdk_include}")
target_compile_options(mod PRIVATE /W4 /utf-8)
target_compile_definitions(mod PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
target_link_options(mod PRIVATE /INCREMENTAL:NO)
set_target_properties(mod PROPERTIES OUTPUT_NAME "${MOD_ID}")

configure_file(mod.json.in "${CMAKE_CURRENT_BINARY_DIR}/mod.json" @ONLY)

# <id>-<version>.t3mod: mod.json, the DLL, and files/ and textures/ if present.
add_custom_target(package
  COMMAND "${CMAKE_COMMAND}"
    "-DMOD_JSON=${CMAKE_CURRENT_BINARY_DIR}/mod.json"
    "-DMOD_DLL=$<TARGET_FILE:mod>"
    "-DCONTENT_DIR=${CMAKE_CURRENT_SOURCE_DIR}"
    "-DSTAGE_DIR=${CMAKE_CURRENT_BINARY_DIR}/package"
    "-DOUTPUT=${CMAKE_CURRENT_BINARY_DIR}/${MOD_ID}-${PROJECT_VERSION}.t3mod"
    -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/package.cmake"
  COMMENT "Packing ${MOD_ID}-${PROJECT_VERSION}.t3mod"
  VERBATIM)
add_dependencies(package mod)
