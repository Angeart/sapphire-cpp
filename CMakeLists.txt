cmake_minimum_required(VERSION 2.8)

#set(CMAKE_VERBOSE_MAKEFILE TRUE)
project(opal CXX)

# find boost
find_package(Boost 1.64.0 REQUIRED)
message("boost include directory : ${Boost_INCLUDE_DIRS}")

# set version info
set(serial "1.0.0")
set(serial_so "1")

#set include directories
message("project directory : ${PROJECT_SOURCE_DIR}")
include_directories(${PROJECT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})

#set sources
set(opal_sources
src/main.cpp
)

add_executable(opal ${opal_sources})
set_target_properties(opal PROPERTIES VERSION ${serial} SOVERSIN ${serial_so})
