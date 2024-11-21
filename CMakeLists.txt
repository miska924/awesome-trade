cmake_minimum_required(VERSION 3.22)
project(AwesomeTrade VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Werror -Wpedantic")

find_package(jsoncpp REQUIRED)
find_package(GTest REQUIRED)
find_package(cpr REQUIRED)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
enable_testing()
include(GoogleTest)
include(CTest)

include_directories(lib)

add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(experiments)
