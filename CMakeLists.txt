cmake_minimum_required(VERSION 3.10)
project(opengt VERSION 1.0.0)

option(ENABLE_PROFILER "Enable code profiling feature" OFF)
option(ENABLE_DEBUG "Enable console log feature" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin/")
set(CMAKE_BUILD_TYPE "Debug")

IF (CMAKE_BUILD_TYPE MATCHES "Debug")
add_definitions(-ggdb -rdynamic -DNDEBUG)
ENDIF(CMAKE_BUILD_TYPE MATCHES "Debug")

IF (CMAKE_BUILD_TYPE MATCHES "Release")
add_definitions(-O3 -DNDEBUG)
ENDIF(CMAKE_BUILD_TYPE MATCHES "Release")

add_subdirectory(OpenGT.Main)