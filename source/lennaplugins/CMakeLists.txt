
# Check if examples are enabled
if(NOT OPTION_BUILD_PLUGINS)
    return()
endif()

# plugins

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MAIN ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/plugins")

add_subdirectory(blur)
add_subdirectory(camera)
add_subdirectory(crop)
add_subdirectory(filechooser)
add_subdirectory(filtermatrix)
add_subdirectory(rename)
add_subdirectory(resize)
add_subdirectory(savefile)
add_subdirectory(textoverlay)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_MAIN})
