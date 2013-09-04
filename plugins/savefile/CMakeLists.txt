cmake_minimum_required(VERSION 2.8.9)
  project(savefile)

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
  
  file( GLOB_RECURSE savefile_SOURCE "*.cpp"  "../../lenna/image.cpp")
file( GLOB_RECURSE savefile_HEADERS "*.h" )
file( GLOB_RECURSE savefile_UI "*.ui" )
file( GLOB_RECURSE savefile_QRC "*.qrc" )
QT5_WRAP_UI( savefile_UI_WRAPPED ${savefile_UI} )
QT5_ADD_RESOURCES( savefile_RES ${savefile_QRC} )

# Specify program and its inputs
	add_library( savefile SHARED
    ${savefile_SOURCE}
    ${savefile_HEADERS}
    ${savefile_UI_WRAPPED}
	${savefile_RES}
    )

  qt5_use_modules(savefile Widgets)
  target_link_libraries( savefile ${OpenCV_LIBS} )
