
# 
# Default dependencies for the runtime-package
# 

# Install 3rd-party runtime dependencies into runtime-component
# install(FILES ... COMPONENT runtime)


# 
# Full dependencies for self-contained packages
# 

if(OPTION_SELF_CONTAINED)

    # Install 3rd-party runtime dependencies into runtime-component
    # install(FILES ... COMPONENT runtime)
	if(WIN32)
                file(TO_CMAKE_PATH $ENV{QT_DIR} QT_FILES)
                file(TO_CMAKE_PATH $ENV{OpenCV_DIR} OpenCV_FILES) 
				
                install(FILES "${QT_FILES}/bin/Qt5Core.dll" "${QT_FILES}/bin/Qt5Gui.dll" "${QT_FILES}/bin/Qt5Widgets.dll" "${QT_FILES}/bin/Qt5Network.dll"
					"${QT_FILES}/bin/Qt5Svg.dll" "${QT_FILES}/bin/libEGL.dll" "${QT_FILES}/bin/opengl32sw.dll"
					"${QT_FILES}/bin/libGLESV2.dll" "${QT_FILES}/bin/D3Dcompiler_47.dll"
                    "${OpenCV_FILES}/x64/vc15/bin/opencv_world450.dll" DESTINATION ${INSTALL_BIN} COMPONENT runtime)
				install(FILES "${QT_FILES}/plugins/platforms/qwindows.dll" DESTINATION ${INSTALL_BIN}/platforms COMPONENT runtime)
				install(FILES "${QT_FILES}/plugins/imageformats/qgif.dll" "${QT_FILES}/plugins/imageformats/qico.dll"
							"${QT_FILES}/plugins/imageformats/qjpeg.dll" "${QT_FILES}/plugins/imageformats/qsvg.dll"
							"${QT_FILES}/plugins/imageformats/qtiff.dll" "${QT_FILES}/plugins/imageformats/qwebp.dll" DESTINATION ${INSTALL_BIN}/imageformats COMPONENT runtime)
	endif()

endif()
