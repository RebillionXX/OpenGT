cmake_minimum_required (VERSION 3.10)
project(opengt.main)
# additional compiler flags -DSIMPLE_PROFILING_ACTIVE

add_definitions(-std=c++17 -DENABLE_PROFILER -DOPENGT_MAIN -D_DEBUG)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../bin/linuxserver")
set(CMAKE_BUILD_TYPE "Debug")

IF (CMAKE_BUILD_TYPE MATCHES "Debug")
add_definitions(-ggdb -rdynamic -DNDEBUG)
ENDIF(CMAKE_BUILD_TYPE MATCHES "Debug")

IF (CMAKE_BUILD_TYPE MATCHES "Release")
add_definitions(-O3 -DNDEBUG)
ENDIF(CMAKE_BUILD_TYPE MATCHES "Release")

include_directories(../../shared)
include_directories(../../source/OpenGT.Main)
#include_directories(../Lunar.Shared/Network/enet/include)

# add_executable(gt.control
#     ../../shared/App.cpp
#     ../../shared/BaseApp.cpp
#     ../../shared/PlatformSetup.cpp
#     ../../shared/Network/PacketUtils.cpp
#     ../../shared/Server/ServerUtils.cpp
#     ../../shared/Util/Logger.cpp
#     ../../shared/Util/MiscUtils.cpp
#     ../../shared/Util/Profile.cpp
#     ../../shared/Util/ResourceUtils.cpp
#     ../../shared/Util/TextScanner.cpp
#  
#     ../../shared/Util/FileSystem/FileSystem.cpp
#     ../../shared/Util/FileSystem/FileManager.cpp
#     ../../shared/Util/FileSystem/StreamingInstance.cpp
#     ../../shared/Util/FileSystem/StreamingInstanceFile.cpp
# 
#     ../../source/Lunar.Logon/Main.cpp
# )

add_executable(opengt.main
    ../../shared/BaseApp.cpp
    ../../shared/PlatformSetup.cpp
    ../../shared/Common/CommonDef.cpp
    ../../shared/Common/CommonServerDef.cpp
    ../../shared/Util/MiscUtils.cpp

    ../../source/OpenGT.Main/Main.cpp
    ../../source/OpenGT.Main/App.cpp
)

include_directories(/usr/include)
include_directories(/usr/include/mysql)
link_directories(/usr/lib/x86_64-linux-gnu)
link_directories(/usr/lib/mysql) 

target_precompile_headers(opengt.main PRIVATE
    ../../shared/pch.h
)

target_link_libraries(opengt.main PRIVATE
    mysqlclient
    # z
)
