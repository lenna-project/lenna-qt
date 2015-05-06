cmake_minimum_required(VERSION 2.8.11)
 project(textoverlay)
  
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
  
 file( GLOB_RECURSE textoverlay_SOURCE "*.cpp"  "../../lenna/image.cpp")
 file( GLOB_RECURSE textoverlay_HEADERS "*.h" )
 file( GLOB_RECURSE textoverlay_UI "*.ui" )
 file( GLOB_RECURSE textoverlay_QRC "*.qrc" )

 qt5_wrap_ui( textoverlay_UI_WRAPPED ${textoverlay_UI} )
 qt5_add_resources( textoverlay_RES ${textoverlay_QRC} )

 add_library( textoverlay SHARED
	${textoverlay_SOURCE}
	${textoverlay_HEADERS}
	${textoverlay_UI_WRAPPED}
	${textoverlay_RES}
)

 qt5_use_modules(textoverlay Widgets Network WebKit WebKitWidgets)
 target_link_libraries( textoverlay Qt5::Core Qt5::Widgets Qt5::WebKit Qt5::WebKitWidgets ${OpenCV_LIBS} )
