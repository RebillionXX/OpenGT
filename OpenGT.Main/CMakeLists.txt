cmake_minimum_required (VERSION 3.10)
project(opengt.main)

add_definitions(-DOPENGT_MAIN)

include_directories(../shared)
include_directories(../OpenGT.Main)
#include_directories(../Lunar.Shared/Network/enet/include)

add_executable(opengt.main
    ../shared/BaseApp.cpp
    ../shared/ConfigBase.cpp
    ../shared/PlatformSetup.cpp
    ../shared/Common/CommonDef.cpp
    ../shared/Common/CommonServerDef.cpp
    ../shared/Engine/RingBuffer.cpp
    ../shared/Logger/LogFileBase.cpp
    ../shared/Logger/LogFileA.cpp
    ../shared/Logger/LogFileW.cpp
    ../shared/Network/NetUtils.cpp
    ../shared/Network/NetworkServerSocket.cpp
    ../shared/Util/MiscUtils.cpp
    ../shared/Util/ResourceUtils.cpp
    ../shared/Util/TextParser.cpp
    
    ../shared/Util/FileSystem/FileSystem.cpp
    ../shared/Util/FileSystem/FileManager.cpp
    ../shared/Util/FileSystem/StreamingInstance.cpp
    ../shared/Util/FileSystem/StreamingInstanceFile.cpp

    ../OpenGT.Main/Main.cpp
    ../OpenGT.Main/App.cpp
    ../OpenGT.Main/MainConfig.cpp
    ../OpenGT.Main/Node/NodeSession.cpp
    ../OpenGT.Main/Node/NodeSessionManager.cpp
)

include_directories(/usr/include)
include_directories(/usr/include/mysql)
link_directories(/usr/lib/x86_64-linux-gnu)
link_directories(/usr/lib/mysql) 

target_precompile_headers(opengt.main PRIVATE
    ../shared/pch.h
)

target_link_libraries(opengt.main PRIVATE
    mysqlclient
    # z
)

target_compile_definitions(opengt.main PRIVATE
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    _CRT_SECURE_NO_WARNINGS
    $<$<BOOL:${ENABLE_PROFILER}>:ENABLE_PROFILER>
    $<$<BOOL:${ENABLE_DEBUG}>:_DEBUG>
)