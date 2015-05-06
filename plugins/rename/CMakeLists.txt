cmake_minimum_required(VERSION 2.8.11)
project(rename)

 set(CMAKE_AUTOMOC ON)
 set(CMAKE_INCLUDE_CURRENT_DIR ON)

 find_package(Qt5Core REQUIRED)
 find_package(Qt5Widgets REQUIRED)
 find_package(Qt5Sql REQUIRED)
 find_package(Qt5LinguistTools REQUIRED)
 find_package(Qt5WebKit REQUIRED)
 find_package(Qt5WebKitWidgets REQUIRED)
 find_package( OpenCV REQUIRED )

include_directories (../../lenna)
  
file( GLOB_RECURSE rename_SOURCE "*.cpp"  "../../lenna/image.cpp")
file( GLOB_RECURSE rename_HEADERS "*.h" )
file( GLOB_RECURSE rename_UI "*.ui" )
file( GLOB_RECURSE rename_QRC "*.qrc" )
QT5_WRAP_UI( rename_UI_WRAPPED ${rename_UI} )
QT5_ADD_RESOURCES( rename_RES ${rename_QRC} )

add_library( rename SHARED
	${rename_SOURCE}
	${rename_HEADERS}
	${rename_UI_WRAPPED}
	${rename_RES}
)

 qt5_use_modules( rename Widgets Network WebKit WebKitWidgets)
 target_link_libraries( rename Qt5::Core Qt5::Widgets Qt5::WebKit Qt5::WebKitWidgets ${OpenCV_LIBS} )
