cmake_minimum_required(VERSION 3.5)
project(AimTux)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ldl")

file(GLOB SOURCE_FILES src/*.cpp)
add_library(AimTux SHARED ${SOURCE_FILES})