cmake_minimum_required(VERSION 3.29)
project(stats)

# Allow the project to work with c and c++.
file(GLOB csources "${PROJECT_SOURCE_DIR}/*.[ch]")
set_property(SOURCE ${csources} PROPERTY CMAKE_C_STANDARD 11)
file(GLOB cppsources "${PROJECT_SOURCE_DIR}/*.cc")
set_property(SOURCE ${cppsources} PROPERTY CMAKE_CXX_STANDARD 14)
set_property(SOURCE ${cppsources} PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)

# Set up GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

# this library doesn't need a test (exe) and
# thus doesn't need to stitch things together w/ target_link_libraries
add_library(cjson "cJSON.c" "cJSON.h")
add_library(server "server.c" "server.h")

add_library(stats "stats.c" "stats.h")
add_executable(test_stats "test_stats.cc")
target_link_libraries(test_stats GTest::gtest_main stats server cjson)

# Each library looks like this.
add_executable(main "main.c")
target_link_libraries(main server stats cjson )