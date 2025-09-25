cmake_minimum_required(VERSION 3.19)
project(AR4_PickAndPlace LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core SerialPort)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
# find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(OpenCV 4 REQUIRED)
# find_package(Qt6 REQUIRED COMPONENTS SerialPort)

qt_standard_project_setup()

qt_add_resources(MyQtApp_RESOURCES resources.qrc)

qt_add_executable(AR4_PickAndPlace
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${MyQtApp_RESOURCES}
    calibrationtab.h calibrationtab.cpp calibrationtab.ui
    robotcontrol.h robotcontrol.cpp robotcontrol.ui
    settings.h settings.cpp settings.ui
    objectdetectiontab.h objectdetectiontab.cpp objectdetectiontab.ui
    cameraworker.h cameraworker.cpp
    robotcontrollerworker.h robotcontrollerworker.cpp
)

target_link_libraries(AR4_PickAndPlace
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::SerialPort
        ${OpenCV_LIBS}
)

target_link_libraries(AR4_PickAndPlace PRIVATE Qt6::Core)
target_link_libraries(AR4_PickAndPlace PRIVATE Qt6::SerialPort)

include(GNUInstallDirs)

install(TARGETS AR4_PickAndPlace
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET AR4_PickAndPlace
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
