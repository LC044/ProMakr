cmake_minimum_required(VERSION 3.5)

project(OneMarkdown VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置 Qt 库的地址（按需设置）
# set(QT_PATH "D:\\ProgramData\\Qt\\Qt5.12.12\\5.12.12\\mingw73_64")
set(QT_PATH "D:\\ProgramData\\Qt\\Qt5.12.12\\5.12.12\\msvc2017_64")
set(CMAKE_PREFIX_PATH ${QT_PATH}/lib/cmake)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets WebEngineWidgets WebChannel REQUIRED)


find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
# set(TS_FILES OneMarkdown_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        OneMarkdown.cpp
        OneMarkdown.h
        OneMarkdown.ui
        ${TS_FILES}
)
if(MATRIX_BUILD AND NOT MATRIX_SUBBUILD AND NOT QT_SUPERBUILD)
    add_build(webengine_webrtc OFF)
    add_build(webengine_proprietary_codecs ON)
    add_build(webengine_printing_and_pdf OFF)
    add_build(webengine_extensions OFF)
    add_build(webengine_spellchecker OFF)
    add_build(qtwebengine_build OFF)
    return()
endif()
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(OneMarkdown
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET OneMarkdown APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(OneMarkdown SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(OneMarkdown
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(OneMarkdown PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(OneMarkdown PRIVATE Qt${QT_VERSION_MAJOR}::WebEngineWidgets Qt${QT_VERSION_MAJOR}::WebChannel)

set_target_properties(OneMarkdown PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(OneMarkdown)
endif()

# ------------------------------------------------------------------------------

if(${MADDY_BUILD_WITH_TESTS})
  add_subdirectory(tests)
endif()

# ------------------------------------------------------------------------------

if(${MADDY_CREATE_PACKAGE})
  set(MADDY_PACKAGE_FILES include/ CMakeLists.txt LICENSE)
  add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-src.zip
    COMMAND ${CMAKE_COMMAND} -E tar c ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-src.zip --format=zip -- ${MADDY_PACKAGE_FILES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${MADDY_PACKAGE_FILES})
  add_custom_target(${PROJECT_NAME}_package DEPENDS ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-src.zip)
endif()
