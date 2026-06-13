# cmake/Packaging.cmake
message(STATUS "Configuring DEB packaging")
install(TARGETS mmedit
    RUNTIME DESTINATION bin
    COMPONENT mmedit
)
install(FILES
    ${CMAKE_SOURCE_DIR}/deploy/linux/mmedit.desktop
    DESTINATION share/applications
    COMPONENT mmedit
)
install(FILES
    ${CMAKE_SOURCE_DIR}/icon/mmedit.svg
    DESTINATION share/icons/hicolor/scalable/apps
    COMPONENT mmedit
)
set(CPACK_COMPONENTS_ALL mmedit)
set(CPACK_COMPONENT_MMEDIT_DISPLAY_NAME "mmedit")
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Build <build@local>")
set(CPACK_DEBIAN_PACKAGE_SECTION "editors")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/rosmapo/mmedit")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Personal reimplementation of Notepad++")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
    "libqt6core6 (>= 6.2) | libqt6core6t64 (>= 6.2), \
     libqt6gui6 (>= 6.2) | libqt6gui6t64 (>= 6.2), \
     libqt6widgets6 (>= 6.2) | libqt6widgets6t64 (>= 6.2), \
     libqt6network6 (>= 6.2) | libqt6network6t64 (>= 6.2), \
     libqt6printsupport6 (>= 6.2) | libqt6printsupport6t64 (>= 6.2), \
     libqt6core5compat6 (>= 6.2), libhunspell-1.7-0, libgl1"
)
set(CPACK_DEBIAN_MMEDIT_PACKAGE_FILE_NAME "mmedit-${PROJECT_VERSION}")
set(CPACK_DEBIAN_MMEDIT_PACKAGE_NAME "mmedit")
include(CPack)