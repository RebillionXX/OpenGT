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
    
public:
    CApp();
    virtual ~CApp();

    bool Create();
    void Destroy();
    void Update();

    virtual void SetupParm() override;
};

extern CApp* g_pApp;
extern CLogFileA* g_pLog;