#
#
#
#

set(PROJECT_NAME "keyboard-backlight")

cmake_minimum_required(VERSION 2.8)
project(${PROJECT_NAME})

include(FindPkgConfig)
include(CMakePackageConfigHelpers)
pkg_search_module(UDEV REQUIRED libudev)

set(KB_BIN "keyboard-backlight")
set(KB_INCLUDE "${PROJECT_SOURCE_DIR}/include")
set(KB_SRC "${PROJECT_SOURCE_DIR}/src")

# Uncomment to make makefiles verbose
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Compiler Options
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall -Wextra -Wpedantic")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG -O3")

# Source
add_subdirectory(${KB_SRC})
include_directories(${KB_INCLUDE})
include_directories(${UDEV_INCLUDE_DIRS})

# Library
add_executable(${KB_BIN} ${SOURCE_FILES})
target_link_libraries(${KB_BIN} ${UDEV_LIBRARIES})

# Installation
set(CMAKE_INSTALL_LIBDIR lib)
set(CMAKE_INSTALL_INCLUDEDIR include)
