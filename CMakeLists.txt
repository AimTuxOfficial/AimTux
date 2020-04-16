cmake_minimum_required(VERSION 3.8)
project(Fuzion)
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX)
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 7.0)
        message(FATAL_ERROR "Your GCC seems outdated. Go to https://github.com/AimTuxOfficial/AimTux/wiki/Updating-your-compiler for further instructions. If you have done so and still see this message, run 'git clean -fdx' and try again")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(WARNING "You use Clang, but recommended compiler is G++")
else()
    message(FATAL_ERROR "You must have GCC >= 7.0 installed in order to compile Fuzion. Go to https://github.com/AimTuxOfficial/AimTux/wiki/Updating-your-compiler for further instructions.")
endif()

FUNCTION (EXCLUDE_FILES_FROM_DIR_IN_LIST _InFileList _excludeDirName _verbose)
    foreach (ITR ${_InFileList})
        if ("${_verbose}")
            message(STATUS "ITR=${ITR}")
        endif ("${_verbose}")

        if ("${ITR}" MATCHES "(.*)${_excludeDirName}(.*)") # Check if the item matches the directory name in _excludeDirName
            message(STATUS "Remove Item from List:${ITR}")
            list (REMOVE_ITEM _InFileList ${ITR}) # Remove the item from the list
        endif ("${ITR}" MATCHES "(.*)${_excludeDirName}(.*)")

    endforeach(ITR)
    set(SOURCE_FILES ${_InFileList} PARENT_SCOPE) # Return the SOURCE_FILES variable to the calling parent
ENDFUNCTION (EXCLUDE_FILES_FROM_DIR_IN_LIST)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -ldl -fpic --no-gnu-unique") #gnu-unique will stop us from unloading.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s -fvisibility=hidden -fvisibility-inlines-hidden")
#set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -std=c++17 -Wall -Wno-maybe-uninitialized -Wno-unused-result -ldl -fpic -shared")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE RELEASE)
endif(NOT CMAKE_BUILD_TYPE)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
EXCLUDE_FILES_FROM_DIR_IN_LIST("${SOURCE_FILES}" "${CMAKE_SOURCE_DIR}/src/ImGUI/examples/" FALSE)
EXCLUDE_FILES_FROM_DIR_IN_LIST("${SOURCE_FILES}" "${CMAKE_SOURCE_DIR}/src/ImGUI/fonts" FALSE)
EXCLUDE_FILES_FROM_DIR_IN_LIST("${SOURCE_FILES}" "${CMAKE_SOURCE_DIR}/src/ImGUI/misc" FALSE)
list(APPEND SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/ImGUI/examples/imgui_impl_opengles3.cpp")
list(APPEND SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/ImGUI/examples/libs/gl3w/GL/gl3w.c")

include_directories(${INCLUDE_DIRS})
#some of the imgui crap expects this to be set.
include_directories("${CMAKE_SOURCE_DIR}/src/ImGUI/")
include_directories("${CMAKE_SOURCE_DIR}/src/ImGUI/examples/")
include_directories("${CMAKE_SOURCE_DIR}/src/ImGUI/examples/libs/")
include_directories("${CMAKE_SOURCE_DIR}/src/ImGUI/examples/libs/gl3w/")

add_library(Fuzion SHARED ${SOURCE_FILES})
target_link_libraries(Fuzion dl SDL2 GL)
