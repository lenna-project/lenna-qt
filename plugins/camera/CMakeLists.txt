cmake_minimum_required(VERSION 2.8.9)
  project(camera)

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
 
  file( GLOB_RECURSE camera_SOURCE "*.cpp" "../../lenna/image.cpp")
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

  qt5_use_modules(camera Widgets)
  target_link_libraries( camera ${OpenCV_LIBS} )
