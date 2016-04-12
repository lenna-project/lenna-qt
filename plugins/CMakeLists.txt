########### Subdirectories ###############
cmake_minimum_required(VERSION 3.0.0)
 project(lenna)

# INPUT PLUGINS
 add_subdirectory( filechooser )
 add_subdirectory( camera )
 add_subdirectory( savefile )

# EDIT PLUGINS
 add_subdirectory( blur )
 add_subdirectory( crop )
 add_subdirectory( rename )
 add_subdirectory( resize )
 add_subdirectory( textoverlay )

# OUTPUT PLUGINS
 add_subdirectory( filtermatrix )
