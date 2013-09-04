cmake_minimum_required(VERSION 2.8.9)
	
 ########### Project name ###########
 	PROJECT(Lenna)
 	SET(LENNA_MAJOR "0")
 	SET(LENNA_MINOR "9")
    SET(LENNA_PATCH "2")
 	SET(VERSION "${LENNA_MAJOR}.${LENNA_MINOR}.${LENNA_PATCH}")
 	SET(PACKAGE lenna)
   ######## CMAKE Policy ###############
   if(COMMAND cmake_policy)
    # Works around warnings libraries linked against that don't
    # have absolute paths (e.g. -lpthreads)
    cmake_policy(SET CMP0003 NEW)

    # Works around warnings about escaped quotes in ADD_DEFINITIONS
    # statements.
    cmake_policy(SET CMP0005 NEW)

    # tell CMake to prefer CMake's own CMake modules when available
    # only available from cmake-2.8.4
    if(${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} EQUAL 8 AND ${CMAKE_PATCH_VERSION} GREATER 3)
        cmake_policy(SET CMP0017 NEW)
    endif()

    # cmake-2.6.1 introduces policy cmp0008 decide how to treat full path libraries that do not appear to be valid library file names
    # quote from cvslog "Such libraries worked by accident in the VS IDE and Xcode generators in CMake 2.4 and below."
    if(${CMAKE_MAJOR_VERSION} EQUAL 2 AND ${CMAKE_MINOR_VERSION} GREATER 4 AND ${CMAKE_PATCH_VERSION} GREATER 0)
        cmake_policy(SET CMP0008 OLD)
    endif()
    
    # disable autolinking to qtmain as we have our own main() functions (new in Qt 5.1)
    cmake_policy(SET CMP0020 OLD)
endif()
  ########### Subdirectories ###############

	set(CMAKE_SKIP_RPATH true)
        set( LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin/plugins" )
        set( EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin" )
        set( CMAKE_LIBRARY_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin/plugins" )
	
	IF(NOT CMAKE_BUILD_TYPE)
		SET(CMAKE_BUILD_TYPE Release CACHE STRING
		"Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
		FORCE)
	ENDIF(NOT CMAKE_BUILD_TYPE)

	ADD_SUBDIRECTORY( lenna )
	ADD_SUBDIRECTORY( plugins )
