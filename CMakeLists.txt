cmake_minimum_required(VERSION 2.8)

#set(CMAKE_VERBOSE_MAKEFILE TRUE)
project(opal CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
set(Boost_USE_MULTITHREADED ON)

# find boost
find_package(Boost 1.64.0 REQUIRED)
find_package(Threads REQUIRED)
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

#link libraries
target_link_libraries(opal ${Boost_LIBRARIES})
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(opal PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(opal "${CMAKE_THREAD_LIBS_INIT}")
endif()
