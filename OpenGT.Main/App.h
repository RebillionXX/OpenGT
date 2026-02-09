#pragma once
#include "PlatformSetup.h"
#include "BaseApp.h"
#include "Logger/LogFileBase.h"

class CApp : public CBaseApp
{
private:
    //

protected:
    virtual void SetupParm() override;

public:
    CApp();
    virtual ~CApp();
};

extern CApp* g_pApp;

extern CLogFileBase* g_pLog;