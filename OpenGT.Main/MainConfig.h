#pragma once
#include "ConfigBase.h"

class CMainConfig : public CConfigBase
{
public:
    u32 m_localTcpIP;
    u16 m_localTcpPort;

protected:
    virtual bool OnLoad(const CTextParser& parser) override;
    virtual bool OnReload() override;

public:
    CMainConfig();
    virtual ~CMainConfig(); 
};

extern CMainConfig* g_pConfig;