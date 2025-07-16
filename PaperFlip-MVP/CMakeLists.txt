cmake_minimum_required(VERSION 3.20)
project(PaperFlip)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Try Qt6 first, fallback to Qt5
find_package(Qt6 QUIET COMPONENTS Core Widgets)
if(Qt6_FOUND)
    message(STATUS "Using Qt6")
    set(Qt_VERSION Qt6)
else()
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
    message(STATUS "Using Qt5")
    set(Qt_VERSION Qt5)
endif()

# Add QuaZip - use bundled quazip without complex dependencies
find_package(PkgConfig REQUIRED)
pkg_check_modules(ZLIB REQUIRED zlib)

# Simple QuaZip integration without external dependencies
set(QuaZip_INCLUDE_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/quazip-1.5/quazip
)

# Manual include for QuaZip 
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/quazip-1.5/quazip)

# Add quazip as a simple target
add_subdirectory(libs/quazip-1.5)
set(QuaZip_LIBRARIES quazip1-qt6)

add_executable(PaperFlip
    main.cpp
    MainWindow.cpp
    MainWindow.h
    ReaderWidget.cpp
    ReaderWidget.h
    EPUBManager.cpp
    EPUBManager.h
    Views/PreviewBar.cpp
    Views/PreviewBar.h
    epub_utils.cpp
    epub_utils.h
)

if(Qt6_FOUND)
    target_link_libraries(PaperFlip Qt6::Core Qt6::Widgets ${QuaZip_LIBRARIES} ${ZLIB_LIBRARIES})
else()
    target_link_libraries(PaperFlip Qt5::Core Qt5::Widgets ${QuaZip_LIBRARIES} ${ZLIB_LIBRARIES})
endif()

target_include_directories(PaperFlip PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${QuaZip_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIRS}
)