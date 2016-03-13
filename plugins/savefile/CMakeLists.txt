cmake_minimum_required(VERSION 2.8.11)
  project(savefile)

 set(CMAKE_AUTOMOC ON)
 set(CMAKE_INCLUDE_CURRENT_DIR ON)

 set(OPENCV_BUILD_3RDPARTY_LIBS TRUE CACHE BOOL "Build 3rd party libraries")

 find_package(Qt5Core REQUIRED)
 find_package(Qt5Widgets REQUIRED)
 find_package(Qt5Sql REQUIRED)
 find_package(Qt5LinguistTools REQUIRED)
 find_package(Qt5WebKit REQUIRED)
 find_package(Qt5WebKitWidgets REQUIRED)
 find_package( OpenCV REQUIRED )

  include_directories (../../src)
  
  file( GLOB_RECURSE savefile_SOURCE "*.cpp"  "../../src/image.cpp")
file( GLOB_RECURSE savefile_HEADERS "*.h" )
file( GLOB_RECURSE savefile_UI "*.ui" )
file( GLOB_RECURSE savefile_QRC "*.qrc" )
QT5_WRAP_UI( savefile_UI_WRAPPED ${savefile_UI} )
QT5_ADD_RESOURCES( savefile_RES ${savefile_QRC} )

# Specify program and its inputs
	add_library( savefile SHARED
    ${savefile_SOURCE}
    ${savefile_HEADERS}
    ${savefile_UI_WRAPPED}
	${savefile_RES}
    )

 qt5_use_modules( savefile Widgets Network WebKit WebKitWidgets)
 target_link_libraries( savefile Qt5::Core Qt5::Widgets Qt5::WebKit Qt5::WebKitWidgets ${OpenCV_LIBS} )
