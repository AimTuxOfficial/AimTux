cmake_minimum_required(VERSION 2.8)
project(AimTux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libstdc++")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_library(AimTux SHARED ${SOURCE_FILES})
target_link_libraries(AimTux dl)
