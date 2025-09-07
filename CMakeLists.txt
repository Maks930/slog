cmake_minimum_required(VERSION 3.5)
project(slog
        VERSION 1.0.0
        DESCRIPTION "Simple log library"
        LANGUAGES CXX)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
        is_top_level)


option(SLOG_BUILD_EXAMPLES "Build slog examples" OFF)
#option(SLOG_INSTALL "Generate target for installing slog" ${is_top_level})
#set_if_undefined(SLOG_INSTALL_CMAKEDIR
#    "${CMAKE_INSTALL_LIBDIR}/cmake/slog-${PROJECT_VERSION}" CACHE STRING
#    "Install path for slog package-related CMake files")

if (DEFINED SLOG_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${SLOG_SHARED_LIBS})
endif()

set(CMAKE_CXX_STANDARD 20)

add_library(slog)
add_library(slog::slog ALIAS slog)

include(cmake/utils.cmake)
include(GNUInstallDirs)

set(sources
        include/slog/slog.h
        include/slog/sink.h
        include/slog/LogMessage.h
        include/slog/levels.h
        include/slog/Logger.h
        include/slog/Manager.h

        src/slog.cpp
        src/sink.cpp
        src/LogMessage.cpp
        src/Logger.cpp
        src/Manager.cpp
)

target_sources(slog PRIVATE ${sources})

target_include_directories(slog
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/slog"
)

if (SLOG_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()