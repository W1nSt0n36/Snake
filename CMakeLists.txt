cmake_minimum_required(VERSION 3.5)

project(snake VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/home/admin1/qt/6.7.2/gcc_64/lib/cmake")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(PROJECT_SOURCES
    gui/desktop/main.cpp
    gui/desktop/mainwindow.cpp
    gui/desktop/mainwindow.h
    gui/desktop/mainwindow.ui
    brick_game/snake/snake.h
    brick_game/snake/snake.cpp
    controller/controller.h
    brick_game/Basemodel.h
    brick_game/tetris/backend.h
    brick_game/tetris/backend.cpp
    brick_game/tetris/tetris_model.cpp
    brick_game/tetris/tetris_model.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(snake
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        gui/desktop/mainwindo_0.h gui/desktop/mainwindo_0.cpp gui/desktop/mainwindo_0.ui

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET snake APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(snake SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(snake
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(snake PRIVATE
    ${PROJECT_SOURCE_DIR}/gui/desktop
    ${PROJECT_SOURCE_DIR}/brick_game/snake
    ${PROJECT_SOURCE_DIR}/controller
    ${PROJECT_SOURCE_DIR}/brick_game
    ${PROJECT_SOURCE_DIR}/brick_game/tetris
)

target_link_libraries(snake PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.snake)
endif()
set_target_properties(snake PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS snake
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(snake)
endif()
