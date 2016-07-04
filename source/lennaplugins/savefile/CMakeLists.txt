
# 
# External dependencies
# 


# Enable automoc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(AUTOMOC_MOC_OPTIONS PROPERTIES FOLDER CMakeAutomocTargets)
set_property(GLOBAL PROPERTY AUTOMOC_FOLDER CMakeAutomocTargets)

# ENABLE CMP0020: Automatically link Qt executables to qtmain target on Windows.
set_policy(CMP0020 NEW)


# 
# Executable name and options
# 

# Target name
set(target savefile)

# Exit here if required dependencies are not met
if (NOT Qt5Core_FOUND)
    message(STATUS "Plugin ${target} skipped: Qt5 not found")
    return()
else()
    message(STATUS "Plugin ${target}")
endif()


# 
# Sources
# 

file(GLOB sources
"*.cpp" "*.h" "*.ui" "*.qrc")


# 
# Create executable
# 

# Build executable
add_library(${target}
    ${sources}
)

# Create namespaced alias
add_library(${META_PROJECT_NAME}::${target} ALIAS ${target})


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
    ${DEFAULT_INCLUDE_DIRECTORIES}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_BINARY_DIR}/source/include
)


# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LIBRARIES}
    ${META_PROJECT_NAME}::lennaplugin
)


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
)


# 
# Deployment
# 

# Executable
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}/plugins    COMPONENT plugins
    LIBRARY DESTINATION ${INSTALL_SHARED}/plugins COMPONENT plugins
    BUNDLE  DESTINATION ${INSTALL_BIN}/plugins COMPONENT plugins
)
