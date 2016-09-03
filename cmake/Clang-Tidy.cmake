file(GLOB_RECURSE ALL_SOURCE_FILES "*.cpp" "*.h")
foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
    string(FIND "${SOURCE_FILE}" "${CMAKE_BINARY_DIR}" PROJECT_TRDPARTY_DIR_FOUND)
    if (NOT "${PROJECT_TRDPARTY_DIR_FOUND}" EQUAL "-1")
        list(REMOVE_ITEM ALL_SOURCE_FILES "${SOURCE_FILE}")
    endif ()
endforeach ()

# Adding clang-tidy target if executable is found
find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
  add_custom_target(
    clang-tidy
    COMMAND clang-tidy
    ${ALL_SOURCE_FILES}
    -config=''
    --
    -std=c++11
    ${INCLUDE_DIRECTORIES}
    )
endif()

