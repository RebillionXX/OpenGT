#pragma once
#include "PlatformSetup.h"
#include "BaseApp.h"
#include "MainConfig.h"
#include "Logger/LogFileA.h"

class CApp : public CBaseApp
{
private:

public:
    // Main Logger's Thread ID
    i32 m_mainLogIdx;
    
    // Server List
    u32 m_commonServerCount;
    SERVER_INFO_COMMON m_aCommonServerList[ASC_SERVER_COUNT];

    // SERVER_INFO_GAME m_aGameServerList[MAX_GAME_SERVER_COUNT];

public:
    CApp();
    virtual ~CApp();

    bool Create();
    void Destroy();
    void Update();

    virtual void SetupParm() override;

    u32 GetServerCount() { return m_commonServerCount; /* + m_gameServerCount + ...*/}
};

extern CApp* g_pApp;
extern CLogFileA* g_pLog;