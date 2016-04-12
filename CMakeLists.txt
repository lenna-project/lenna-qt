cmake_minimum_required(VERSION 2.8.11)
	
 ########### Project name ###########
 project(lenna)

 file (STRINGS "${PROJECT_SOURCE_DIR}/VERSION" PACKAGE_VERSION )
 string(REGEX REPLACE "([0-9]+)\\.[0-9]+\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MAJOR ${PACKAGE_VERSION})
 string(REGEX REPLACE "[0-9]+\\.([0-9])+\\.[0-9]+.*" "\\1" CPACK_PACKAGE_VERSION_MINOR ${PACKAGE_VERSION})
 string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" CPACK_PACKAGE_VERSION_PATCH ${PACKAGE_VERSION})
 set(COMPLETE_VERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH})
 set(RELEASE_NAME "Unstable-trunk")
 set(PROJECT_VERSION ${COMPLETE_VERSION})
 set(PACKAGE lenna)

 ########### Subdirectories ###############

 set(CMAKE_SKIP_RPATH true)
 set( LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin/plugins" )
 set( EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin" )
 set( CMAKE_LIBRARY_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin/plugins" )
	
 if(NOT CMAKE_BUILD_TYPE)
 set(CMAKE_BUILD_TYPE Release CACHE STRING
		"Choose the type of build, options are: None Debug Release."
		FORCE)
 endif(NOT CMAKE_BUILD_TYPE)

 add_definitions(-std=c++11)

 option(BUILD_DOCUMENTATION "Create doxygen documentation for developers" OFF)

 add_subdirectory( src )
 add_subdirectory( plugins )
 add_subdirectory( doc )
