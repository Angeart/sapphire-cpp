cmake_minimum_required(VERSION 3.10)

project(sapphire CXX C)

# find boost
find_package(Boost 1.62.0 REQUIRED)
find_package(Threads REQUIRED)
message("boost include directory : ${Boost_INCLUDE_DIRS}")

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    add_definitions(-DDEBUG)
else()
    add_definitions(-DRELEASE)
endif()

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
