cmake_minimum_required(VERSION 2.8.9)
  project(filechooser)

  cmake_policy(SET CMP0020 OLD)
  # Tell CMake to run moc when necessary:
  set(CMAKE_AUTOMOC ON)
  # As moc files are generated in the binary dir, tell CMake
  # to always look for includes there:
  set(CMAKE_INCLUDE_CURRENT_DIR ON)

  # Widgets finds its own dependencies.
  find_package(Qt5Widgets REQUIRED)
  find_package( OpenCV REQUIRED )

  include_directories (../../lenna)
 
  file( GLOB_RECURSE filechooser_SOURCE "*.cpp" "../../lenna/image.cpp")
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

  qt5_use_modules(filechooser Widgets)
  target_link_libraries( filechooser ${OpenCV_LIBS} )
