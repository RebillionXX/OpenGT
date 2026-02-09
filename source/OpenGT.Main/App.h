#pragma once
#include "BaseApp.h"

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