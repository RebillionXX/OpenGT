#include "MainConfig.h"
#include "Network/NetUtils.h"

CMainConfig* g_pConfig = NULL;

CMainConfig::CMainConfig() : CConfigBase()
{
    //
}

CMainConfig::~CMainConfig()
{
    //
}

bool CMainConfig::OnLoad(const std::vector<ConfigEntry>& entries)
{
    for (i32 i = 0; i < (i32)entries.size(); i++)
    {
        const ConfigEntry& entry = entries[i];
        if (entry.m_key == "common")
        {
            m_localTcpIP    = NetUtil::StringToIPV4(entry.m_values[0]);
            m_localTcpPort  = (u16)StringToInt(entry.m_values[1]);
        }
    }

    
	char szAddrIP[32];
    NetUtil::IPV4ToString(m_localTcpIP, szAddrIP);

    g_pLog->WriteDebug("LOCAL IP/PORT %s:%i - %i", szAddrIP, m_localTcpPort, m_localTcpIP);
    return true;
}

bool CMainConfig::OnReload()
{
    return true;
}