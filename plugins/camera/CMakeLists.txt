cmake_minimum_required(VERSION 2.8.11)
  project(camera)

 set(CMAKE_AUTOMOC ON)
 set(CMAKE_INCLUDE_CURRENT_DIR ON)

 find_package(Qt5Core REQUIRED)
 find_package(Qt5Widgets REQUIRED)
 find_package(Qt5Sql REQUIRED)
 find_package(Qt5LinguistTools REQUIRED)
 find_package(Qt5WebKit REQUIRED)
 find_package(Qt5WebKitWidgets REQUIRED)
 find_package( OpenCV REQUIRED )

  include_directories (../../src)
 
  file( GLOB_RECURSE camera_SOURCE "*.cpp" "../../src/image.cpp")
file( GLOB_RECURSE camera_HEADERS "*.h")
file( GLOB_RECURSE camera_UI "*.ui" )
file( GLOB_RECURSE camera_QRC "*.qrc" )
QT5_WRAP_UI( camera_UI_WRAPPED ${camera_UI} )
QT5_ADD_RESOURCES( camera_RES ${camera_QRC} )

# Specify program and its inputs
add_library( camera SHARED
    ${camera_SOURCE}
    ${camera_HEADERS}
    ${camera_UI_WRAPPED}
	${camera_RES}
    )

 qt5_use_modules(camera Widgets Network WebKit WebKitWidgets)
 target_link_libraries( camera Qt5::Core Qt5::Widgets Qt5::WebKit Qt5::WebKitWidgets ${OpenCV_LIBS} )
