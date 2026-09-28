# Packs the mod as a .t3mod (docs/mods.md in T3SDK): a zip with mod.json and
# the DLL at its root, plus the project's files/ and textures/ when they hold
# anything but their README.md. Entries are sorted, with no folder entries and
# a fixed modification time. Run by the `package` target:
#
#   cmake -DMOD_JSON=<mod.json> -DMOD_DLL=<dll> -DCONTENT_DIR=<project folder>
#         -DSTAGE_DIR=<scratch folder> -DOUTPUT=<id>-<version>.t3mod -P package.cmake
cmake_minimum_required(VERSION 3.25)

foreach(var MOD_JSON MOD_DLL CONTENT_DIR STAGE_DIR OUTPUT)
  if(NOT DEFINED ${var})
    message(FATAL_ERROR "package.cmake needs -D${var}=...")
  endif()
endforeach()

file(REMOVE_RECURSE "${STAGE_DIR}")
file(MAKE_DIRECTORY "${STAGE_DIR}")
file(COPY "${MOD_JSON}" "${MOD_DLL}" DESTINATION "${STAGE_DIR}")
get_filename_component(dll_name "${MOD_DLL}" NAME)
set(entries mod.json "${dll_name}")

# files/ mirrors the game folder; textures/ holds <texture name>.dds files.
foreach(dir files textures)
  if(NOT IS_DIRECTORY "${CONTENT_DIR}/${dir}")
    continue()
  endif()
  file(GLOB_RECURSE found LIST_DIRECTORIES false RELATIVE "${CONTENT_DIR}" "${CONTENT_DIR}/${dir}/*")
  foreach(path IN LISTS found)
    get_filename_component(name "${path}" NAME)
    string(TOLOWER "${name}" lower)
    if(path STREQUAL "${dir}/README.md" OR lower MATCHES "^(\\.gitkeep|\\.ds_store|thumbs\\.db|desktop\\.ini)$")
      continue()
    endif()
    get_filename_component(folder "${path}" DIRECTORY)
    file(COPY "${CONTENT_DIR}/${path}" DESTINATION "${STAGE_DIR}/${folder}")
    list(APPEND entries "${path}")
  endforeach()
endforeach()

list(SORT entries)
list(JOIN entries "\n" listing)
set(list_file "${STAGE_DIR}.files")
file(WRITE "${list_file}" "${listing}\n")
file(REMOVE "${OUTPUT}")
execute_process(
  COMMAND "${CMAKE_COMMAND}" -E tar cf "${OUTPUT}" --format=zip "--mtime=1980-01-01 00:00:00 UTC"
          "--files-from=${list_file}"
  WORKING_DIRECTORY "${STAGE_DIR}"
  RESULT_VARIABLE result)
if(NOT result EQUAL 0)
  message(FATAL_ERROR "Could not write ${OUTPUT}")
endif()

file(SIZE "${OUTPUT}" size)
file(SHA256 "${OUTPUT}" sha256)
list(LENGTH entries count)
message(STATUS "Wrote ${OUTPUT}: ${count} files, ${size} bytes, sha256 ${sha256}")
