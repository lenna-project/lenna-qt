cmake_minimum_required(VERSION 2.8.11)
  project(filechooser)

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
 
  file( GLOB_RECURSE filechooser_SOURCE "*.cpp" "../../src/image.cpp")
file( GLOB_RECURSE filechooser_HEADERS "*.h")
file( GLOB_RECURSE filechooser_UI "*.ui" )
file( GLOB_RECURSE filechooser_QRC "*.qrc" )
QT5_WRAP_UI( filechooser_UI_WRAPPED ${filechooser_UI} )
QT5_ADD_RESOURCES( filechooser_RES ${filechooser_QRC} )

# Specify program and its inputs
add_library( filechooser SHARED
    ${filechooser_SOURCE}
    ${filechooser_HEADERS}
    ${filechooser_UI_WRAPPED}
	${filechooser_RES}
    )

 qt5_use_modules( filechooser Widgets Network WebKit WebKitWidgets)
 target_link_libraries( filechooser Qt5::Core Qt5::Widgets Qt5::WebKit Qt5::WebKitWidgets ${OpenCV_LIBS} )
