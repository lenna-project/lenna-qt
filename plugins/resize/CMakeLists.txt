cmake_minimum_required(VERSION 2.8.9)
project(resize)

cmake_policy(SET CMP0020 OLD)
  
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package( OpenCV REQUIRED )

include_directories (../../lenna)
  
file( GLOB_RECURSE resize_SOURCE "*.cpp"  "../../lenna/image.cpp")
file( GLOB_RECURSE resize_HEADERS "*.h" )
file( GLOB_RECURSE resize_UI "*.ui" )
file( GLOB_RECURSE resize_QRC "*.qrc" )
QT5_WRAP_UI( resize_UI_WRAPPED ${resize_UI} )
QT5_ADD_RESOURCES( resize_RES ${resize_QRC} )

add_library( resize SHARED
	${resize_SOURCE}
	${resize_HEADERS}
	${resize_UI_WRAPPED}
	${resize_RES}
)

qt5_use_modules(resize Widgets)
target_link_libraries( resize ${OpenCV_LIBS} )
