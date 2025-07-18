cmake_minimum_required(VERSION 3.16)

project(VisualAlgorithms VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appVisualAlgorithms
    src/main.cpp
)

qt_add_qml_module(appVisualAlgorithms
    URI VisualAlgorithms
    VERSION 1.0
    QML_FILES
        src/Main.qml
        SOURCES src/perlinnoise.h src/perlinnoise.cpp
        SOURCES src/valuenoise1d.h src/valuenoise1d.cpp
        SOURCES src/noise.h src/noise.cpp
        SOURCES src/valuenoise2d.h src/valuenoise2d.cpp
        SOURCES src/noisemanager.h src/noisemanager.cpp
        QML_FILES src/NoiseCanvas.qml
        QML_FILES src/InputBar.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appVisualAlgorithms PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appVisualAlgorithms
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appVisualAlgorithms
    PRIVATE Qt6::Quick
    Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appVisualAlgorithms
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
