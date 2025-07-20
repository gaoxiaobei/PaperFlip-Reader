cmake_minimum_required(VERSION 3.16)

project(PaperFlip-Reader VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt's Meta-Object Compiler
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Qt version compatibility
find_package(Qt6 QUIET COMPONENTS Core Widgets)
if(Qt6_FOUND)
    set(QT_VERSION_MAJOR 6)
    message(STATUS "Using Qt6")
else()
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
    set(QT_VERSION_MAJOR 5)
    message(STATUS "Using Qt5")
endif()

# Set source files
set(SOURCES
    src/main.cpp
    src/core/EPUBManager.cpp
    src/core/epub_utils.cpp
    src/ui/MainWindow.cpp
    src/ui/ReaderWidget.cpp
    src/ui/Views/PreviewBar.cpp
)

set(HEADERS
    src/core/EPUBManager.h
    src/core/epub_utils.h
    src/ui/MainWindow.h
    src/ui/ReaderWidget.h
    src/ui/Views/PreviewBar.h
)

# Create executable
add_executable(PaperFlip-Reader
    ${SOURCES}
    ${HEADERS}
)

# QuaZip integration via submodule
option(USE_SYSTEM_QUAZIP "Use system QuaZip instead of submodule" OFF)

if(USE_SYSTEM_QUAZIP)
    # Try to find system QuaZip
    find_package(PkgConfig QUIET)
    if(PkgConfig_FOUND)
        pkg_check_modules(QUAZIP QUIET quazip${QT_VERSION_MAJOR})
    endif()
    
    if(NOT QUAZIP_FOUND)
        find_path(QUAZIP_INCLUDE_DIR quazip.h PATH_SUFFIXES quazip${QT_VERSION_MAJOR})
        find_library(QUAZIP_LIBRARY quazip${QT_VERSION_MAJOR})
        if(QUAZIP_INCLUDE_DIR AND QUAZIP_LIBRARY)
            set(QUAZIP_FOUND TRUE)
            set(QUAZIP_INCLUDE_DIRS ${QUAZIP_INCLUDE_DIR})
            set(QUAZIP_LIBRARIES ${QUAZIP_LIBRARY})
        endif()
    endif()
endif()

if(NOT QUAZIP_FOUND)
    # Use submodule
    if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/quazip/CMakeLists.txt")
        message(FATAL_ERROR "QuaZip submodule not found. Please run: git submodule update --init --recursive")
    endif()
    
    add_subdirectory(external/quazip)
    set(QUAZIP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/external/quazip/quazip)
    set(QUAZIP_LIBRARIES QuaZip)
endif()

# Link libraries
if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(PaperFlip-Reader
        Qt6::Core
        Qt6::Widgets
        ${QUAZIP_LIBRARIES}
    )
else()
    target_link_libraries(PaperFlip-Reader
        Qt5::Core
        Qt5::Widgets
        ${QUAZIP_LIBRARIES}
    )
endif()

# Include directories
target_include_directories(PaperFlip-Reader PRIVATE
    src
    src/core
    src/ui
    src/ui/Views
    ${QUAZIP_INCLUDE_DIRS}
)

# Compiler-specific options
if(MSVC)
    target_compile_options(PaperFlip-Reader PRIVATE /W4)
else()
    target_compile_options(PaperFlip-Reader PRIVATE -Wall -Wextra)
endif()

# Set output directory
set_target_properties(PaperFlip-Reader PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Platform-specific settings
if(WIN32)
    set_target_properties(PaperFlip-Reader PROPERTIES
        WIN32_EXECUTABLE FALSE
    )
endif()

# Install rules
install(TARGETS PaperFlip-Reader
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# CPack configuration
set(CPACK_PACKAGE_NAME "PaperFlip-Reader")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A modern EPUB reader built with Qt")
set(CPACK_PACKAGE_VENDOR "PaperFlip Project")

include(CPack)