cmake_minimum_required(VERSION 3.10)

include(${PROJECT_SOURCE_DIR}/cmake/DownloadProject/DownloadProject.cmake)
download_project(PROJ googletest
                GIT_REPOSITORY https://github.com/google/googletest.git
                GIT_TAG master
                UPDATE_DISCONNECTED 1
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# Prevent overriding the parent project's compiler/linker
# settings on Windows
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(test_sources
test_variable.cpp
test_function.cpp
test_import.cpp
test_one_statement.cpp
test_comment.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/src ${Boost_INCLUDE_DIRS})

add_executable(sapphire_test ${test_sources})
include(GoogleTest)
if(sapphire_for_test)
    target_link_libraries(sapphire_test sapphire_for_test gtest_main ${Boost_LIBRARIES})
else()
    target_link_libraries(sapphire_test gtest_main ${Boost_LIBRARIES})
endif()
gtest_add_tests(TARGET sapphire_test)
