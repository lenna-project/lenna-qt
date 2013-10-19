cmake_minimum_required(VERSION 2.8.9)
project(textoverlay)

cmake_policy(SET CMP0020 OLD)
  
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package( OpenCV REQUIRED )

include_directories (../../lenna)
  
file( GLOB_RECURSE textoverlay_SOURCE "*.cpp"  "../../lenna/image.cpp")
file( GLOB_RECURSE textoverlay_HEADERS "*.h" )
file( GLOB_RECURSE textoverlay_UI "*.ui" )
file( GLOB_RECURSE textoverlay_QRC "*.qrc" )
QT5_WRAP_UI( textoverlay_UI_WRAPPED ${textoverlay_UI} )
QT5_ADD_RESOURCES( textoverlay_RES ${textoverlay_QRC} )

add_library( textoverlay SHARED
	${textoverlay_SOURCE}
	${textoverlay_HEADERS}
	${textoverlay_UI_WRAPPED}
	${textoverlay_RES}
)

qt5_use_modules(textoverlay Widgets)
target_link_libraries( textoverlay ${OpenCV_LIBS} )
