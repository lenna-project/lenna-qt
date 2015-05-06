cmake_minimum_required(VERSION 2.8.11)
	
 ########### Project name ###########
 project(lenna)
 set(LENNA_MAJOR "0")
 set(LENNA_MINOR "9")
 set(LENNA_PATCH "3")
 set(VERSION "${LENNA_MAJOR}.${LENNA_MINOR}.${LENNA_PATCH}")
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

 option(BUILD_DOCUMENTATION "Create doxygen documentation for developers" OFF)

 add_subdirectory( lenna )
 add_subdirectory( plugins )
 add_subdirectory( doc )
