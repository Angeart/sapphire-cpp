cmake_minimum_required(VERSION 3.1)

project(sapphire CXX C)

# find boost
find_package(Boost 1.64.0 REQUIRED)
find_package(Threads REQUIRED)
message("boost include directory : ${Boost_INCLUDE_DIRS}")

enable_testing()
add_subdirectory(src)
add_subdirectory(test)