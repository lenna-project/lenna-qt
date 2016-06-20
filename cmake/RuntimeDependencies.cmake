
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
                set(QT_FILES $ENV{QT_DIR}/bin)
                set(OpenCV_FILES $ENV{OpenCV_DIR}/build/bin/Release)
                install(FILES "${QT_FILES}/Qt5Core.dll" "${QT_FILES}/Qt5Gui.dll" "${QT_FILES}/Qt5Widgets.dll" "${QT_FILES}/Qt5Network.dll"
                    "${OpenCV_FILES}/opencv_world310.dll" "${OpenCV_FILES}/opencv_world310.dll" DESTINATION ${INSTALL_BIN} COMPONENT runtime)
	endif()

endif()
