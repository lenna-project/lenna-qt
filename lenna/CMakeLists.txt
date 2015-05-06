cmake_minimum_required(VERSION 2.8.11)

 project(lenna)

 set(CMAKE_INCLUDE_CURRENT_DIR ON)
 set(CMAKE_AUTOMOC ON)

 find_package(Qt5Core REQUIRED)
 find_package(Qt5Widgets REQUIRED)
 find_package(Qt5Sql REQUIRED)
 find_package(Qt5LinguistTools REQUIRED)
 find_package(Qt5WebKit REQUIRED)
 find_package(Qt5WebKitWidgets REQUIRED)
 find_package( OpenCV REQUIRED )

 file( GLOB_RECURSE lenna_SOURCE "*.cpp" "plugins/*.cpp")
 file( GLOB_RECURSE lenna_HEADERS "*.h" "plugins/*.h")
 file( GLOB_RECURSE lenna_UI "*.ui" "plugins/*.ui")
 file( GLOB_RECURSE lenna_QRC "*.qrc" )

 set(lennalibs Qt5::Core Qt5::Widgets Qt5::WebKit Qt5::WebKitWidgets ${OpenCV_LIBS} )

 qt5_add_resources( lenna_RES ${lenna_QRC} )
 qt5_wrap_ui( lenna_UI_WRAPPED ${lenna_UI} )

 add_executable( lenna
    ${lenna_SOURCE}
    ${lenna_HEADERS}
    ${lenna_UI_WRAPPED}
    ${lenna_RES}
    )

 target_link_libraries( lenna ${lennalibs})
 qt5_use_modules(lenna Widgets Network WebKit WebKitWidgets)
