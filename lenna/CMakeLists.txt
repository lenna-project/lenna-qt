cmake_minimum_required(VERSION 2.8.9)
  project(lenna)

  cmake_policy(SET CMP0020 OLD)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
  set(CMAKE_AUTOMOC ON)  

  # Widgets finds its own dependencies.
  find_package(Qt5Widgets REQUIRED)
  find_package( OpenCV REQUIRED )

file( GLOB_RECURSE lenna_SOURCE "*.cpp" "plugins/*.cpp")
file( GLOB_RECURSE lenna_HEADERS "*.h" "plugins/*.h")
file( GLOB_RECURSE lenna_UI "*.ui" "plugins/*.ui")
file( GLOB_RECURSE lenna_QRC "*.qrc" )
QT5_WRAP_UI( lenna_UI_WRAPPED ${lenna_UI} )
QT5_ADD_RESOURCES( lenna_RES ${lenna_QRC} )

# Specify program and its inputs

add_executable( lenna WIN32
    ${lenna_SOURCE}
    ${lenna_HEADERS}
    ${lenna_UI_WRAPPED}
	${lenna_RES}
    )
  target_link_libraries( lenna ${OpenCV_LIBS} Qt5::Widgets Qt5::WinMain)

qt5_use_modules(lenna Widgets Network)
