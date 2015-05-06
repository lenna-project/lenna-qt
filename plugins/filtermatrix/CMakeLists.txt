cmake_minimum_required(VERSION 2.8.11)
project(filtermatrix)

 set(CMAKE_AUTOMOC ON)
 set(CMAKE_INCLUDE_CURRENT_DIR ON)

 find_package(Qt5Core REQUIRED)
 find_package(Qt5Widgets REQUIRED)
 find_package(Qt5Sql REQUIRED)
 find_package(Qt5LinguistTools REQUIRED)
 find_package(Qt5WebKit REQUIRED)
 find_package(Qt5WebKitWidgets REQUIRED)
 find_package( OpenCV REQUIRED )

 include_directories(../../lenna)
  
file( GLOB_RECURSE _SOURCE "*.cpp"  "../../lenna/image.cpp")
file( GLOB_RECURSE _HEADERS "*.h" )
file( GLOB_RECURSE _UI "*.ui" )
file( GLOB_RECURSE _QRC "*.qrc" )
QT5_WRAP_UI( _UI_WRAPPED ${_UI} )
QT5_ADD_RESOURCES( _RES ${_QRC} )

add_library( filtermatrix SHARED
	${_SOURCE}
	${_HEADERS}
	${_UI_WRAPPED}
	${_RES}
)

 qt5_use_modules( filtermatrix Widgets Network WebKit WebKitWidgets)
 target_link_libraries( filtermatrix Qt5::Core Qt5::Widgets Qt5::WebKit Qt5::WebKitWidgets ${OpenCV_LIBS} )
