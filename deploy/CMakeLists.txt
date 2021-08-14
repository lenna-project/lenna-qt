
# 
# Target 'pack'
# 

add_custom_target(pack)
set_target_properties(pack PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)


# Install additional runtime dependencies
include(${PROJECT_SOURCE_DIR}/cmake/RuntimeDependencies.cmake)


# 
# Packages
# 

include(packages/pack-lenna-qt.cmake)


#
# Target 'component_install'
#

add_custom_target(
    component_install
    COMMAND make preinstall
    COMMAND ${CMAKE_COMMAND} -P ${PROJECT_SOURCE_DIR}/cmake/ComponentInstall.cmake
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

configure_file(packages/snapcraft.yaml.in ${PROJECT_BINARY_DIR}/snapcraft.yaml)
configure_file(packages/qt5-launch ${PROJECT_BINARY_DIR}/qt5-launch)
configure_file(packages/snappy-qt5.conf.in ${PROJECT_BINARY_DIR}/snappy-qt5.conf)

add_custom_target(
    snap
    COMMAND snapcraft snap
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
