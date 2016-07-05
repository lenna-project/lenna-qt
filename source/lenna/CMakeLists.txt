
#
# External dependencies
#

# find_package(THIRDPARTY REQUIRED)


# Enable automoc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(AUTOMOC_MOC_OPTIONS PROPERTIES FOLDER CMakeAutomocTargets)
set_property(GLOBAL PROPERTY AUTOMOC_FOLDER CMakeAutomocTargets)

# ENABLE CMP0020: Automatically link Qt executables to qtmain target on Windows.
cmake_policy(SET CMP0020 NEW)

#
# Library name and options
#

# Target name
set(target lenna)

# Exit here if required dependencies are not met
message(STATUS "Exe ${target}")


# Set API export file and macro
string(TOUPPER ${target} target_upper)
set(feature_file "include/${target}/${target}_features.h")
set(export_file  "include/${target}/${target}_api.h")
set(export_macro "${target_upper}_API")


#
# Sources
#

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(source_path  "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(resource_path  "${CMAKE_CURRENT_SOURCE_DIR}/resource")

configure_file(${include_path}/defines.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/defines.h)

file(GLOB headers
"${include_path}/*.h"
"${include_path}/plugins/*.h"
)

file(GLOB sources
"${source_path}/*.cpp"
"${source_path}/plugins/*.cpp"
)

file(GLOB uis
"${source_path}/*.ui"
"${source_path}/plugins/*.ui"
)

file(GLOB resources "${resource_path}/*.qrc" )

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$"
    ${header_group} ${headers})
source_group_by_path(${source_path}  "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$"
    ${source_group} ${sources})


#
# Create executable
#

# Build executable
add_executable(${target}
    MACOSX_BUNDLE
    ${sources}
    ${headers}
    ${uis}
    ${resources}
)

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})


#
# Project options
#

set_target_properties(${target}
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER "${IDE_FOLDER}"
)


#
# Include directories
#

target_include_directories(${target}
    PRIVATE
    ${include_path}
    ${PROJECT_BINARY_DIR}/source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/source
    ${CMAKE_CURRENT_BINARY_DIR}

    PUBLIC
    ${DEFAULT_INCLUDE_DIRECTORIES}

    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


#
# Libraries
#

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LIBRARIES}
    ${META_PROJECT_NAME}::lennaplugin)


#
# Compile definitions
#

target_compile_definitions(${target}
    PRIVATE
    ${DEFAULT_COMPILE_DEFINITIONS}
)


#
# Compile options
#

target_compile_options(${target}
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)


#
# Linker options
#

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
    ${META_PROJECT_NAME}::lennaplugin
)


#
# Deployment
#

# Executable
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT runtime
    BUNDLE  DESTINATION ${INSTALL_BIN} COMPONENT runtime
)
