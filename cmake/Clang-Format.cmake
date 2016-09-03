file(GLOB_RECURSE ALL_SOURCE_FILES "*.cpp" "*.h")
foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
    string(FIND "${SOURCE_FILE}" "${CMAKE_BINARY_DIR}" PROJECT_TRDPARTY_DIR_FOUND)
    if (NOT "${PROJECT_TRDPARTY_DIR_FOUND}" EQUAL "-1")
        list(REMOVE_ITEM ALL_SOURCE_FILES "${SOURCE_FILE}")
    endif ()
endforeach ()

# Adding clang-tidy target if executable is found
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
 add_custom_target(
  clang-format
  COMMAND clang-format
  -style=file -i
  ${ALL_SOURCE_FILES}
 )
endif()
