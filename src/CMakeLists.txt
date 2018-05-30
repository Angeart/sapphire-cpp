#set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
set(Boost_USE_MULTITHREADED ON)

# set version info
set(serial "1.0.0")
set(serial_so "1")

#set include directories
message("project directory : ${PROJECT_SOURCE_DIR}/src")
include_directories(${PROJECT_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS})

#set sources
set(sapphire_sources_without_main
)
set(sapphire_sources
${sapphire_sources_without_main}
main.cpp
)

add_executable(sapphire ${sapphire_sources})
if(sapphire_sources_without_main)
  add_library(sapphire_for_test STATIC ${sapphire_sources_without_main})
endif()
set_target_properties(sapphire PROPERTIES VERSION ${serial} SOVERSIN ${serial_so})

#link libraries
target_link_libraries(sapphire ${Boost_LIBRARIES})
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(sapphire PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(sapphire "${CMAKE_THREAD_LIBS_INIT}")
endif()
