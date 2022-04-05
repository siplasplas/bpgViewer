cmake_minimum_required(VERSION 3.5)

project(bpgviewer VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

link_directories(libbpg)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        qbetterportablegraphics.cpp
        qbetterportablegraphics.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(bpgviewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET bpgviewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(bpgviewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(bpgviewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

set(BPG_SOURCES
        libbpg/libbpg.c
        libbpg/bpgenc.c
        libbpg/bpgdec.c
        #libbpg/bpgview.c
        libbpg/libavutil/mem.c
        libbpg/libavutil/buffer.c
        libbpg/libavutil/log2_tab.c
        libbpg/libavutil/frame.c
        libbpg/libavutil/pixdesc.c
        libbpg/libavutil/md5.c
        libbpg/libavcodec/hevc_cabac.c
        libbpg/libavcodec/hevc_filter.c
        libbpg/libavcodec/hevc.c
        libbpg/libavcodec/hevcpred.c
        libbpg/libavcodec/hevc_refs.c
        libbpg/libavcodec/hevcdsp.c
        libbpg/libavcodec/hevc_mvs.c
        libbpg/libavcodec/hevc_ps.c
        libbpg/libavcodec/hevc_sei.c
        libbpg/libavcodec/utils.c
        libbpg/libavcodec/cabac.c
        libbpg/libavcodec/golomb.c
        libbpg/libavcodec/videodsp.c
        )

add_library(bpg STATIC ${BPG_SOURCES})
file (STRINGS "libbpg/VERSION" VERSION)
target_compile_definitions(bpg PUBLIC -DCONFIG_BPG_VERSION=\"${VERSION}\")
target_compile_definitions(bpg PUBLIC -D_FILE_OFFSET_BITS=64)
target_compile_definitions(bpg PUBLIC -D_LARGEFILE_SOURCE)
target_compile_definitions(bpg PUBLIC -D_REENTRANT)
target_compile_definitions(bpg PUBLIC -DHAVE_AV_CONFIG_H)
add_definitions("-Os -Wall -MMD -fno-asynchronous-unwind-tables -fdata-sections -ffunction-sections -fno-math-errno -fno-signed-zeros -fno-tree-vectorize -fomit-frame-pointer")
target_include_directories(bpg
        PRIVATE
        libbpg
        )

target_link_libraries(bpgviewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
            bpg png
            )

set_target_properties(bpgviewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(bpgviewer)
endif()
