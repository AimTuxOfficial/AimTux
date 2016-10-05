cmake_minimum_required(VERSION 3.0)
project(AimTux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(AimTux SHARED ${SOURCE_FILES})
target_link_libraries(AimTux dl)
