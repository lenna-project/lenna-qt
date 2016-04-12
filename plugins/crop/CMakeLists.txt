cmake_minimum_required(VERSION 3.0.0)
project(crop)

 set(CMAKE_AUTOMOC ON)
 set(CMAKE_INCLUDE_CURRENT_DIR ON)

 find_package(Qt5Core REQUIRED)
 find_package(Qt5Widgets REQUIRED)
 find_package(Qt5Sql REQUIRED)
 find_package(Qt5LinguistTools REQUIRED)
 find_package(Qt5WebKit REQUIRED)
 find_package(Qt5WebKitWidgets REQUIRED)
 find_package( OpenCV REQUIRED )

 include_directories (../../src)
  
 file( GLOB_RECURSE ${PROJECT_NAME}_SOURCE "*.cpp"  "../../src/image.cpp")
 file( GLOB_RECURSE ${PROJECT_NAME}_HEADERS "*.h" )
 file( GLOB_RECURSE ${PROJECT_NAME}_UI "*.ui" )
 file( GLOB_RECURSE ${PROJECT_NAME}_QRC "*.qrc" )
 QT5_WRAP_UI( ${PROJECT_NAME}_UI_WRAPPED ${${PROJECT_NAME}_UI} )
 QT5_ADD_RESOURCES( ${PROJECT_NAME}_RES ${${PROJECT_NAME}_QRC} )

 add_library( ${PROJECT_NAME} SHARED
        ${${PROJECT_NAME}_SOURCE}
        ${${PROJECT_NAME}_HEADERS}
        ${${PROJECT_NAME}_UI_WRAPPED}
        ${${PROJECT_NAME}_RES}
 )

 qt5_use_modules(${PROJECT_NAME} Widgets)
 target_link_libraries( ${PROJECT_NAME} Qt5::Core ${OpenCV_LIBS} )
