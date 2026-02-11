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

bool CMainConfig::OnLoad(const CTextParser& parser)
{
    g_pApp->m_commonServerCount = 0;

    for (i32 i = 0; i < m_parser.GetLineCount(); i++)
    {
        std::string line = m_parser.GetLine(i);
        if (line.empty() || line[0] == '#' || (line.size() > 1 && line[0] == '/' && line[1] == '/'))
            continue;

        std::vector<std::string> tokens = m_parser.TokenizeLine(i);
        if (tokens.empty() || tokens.size() <= 1)
            continue;

        if (tokens[0] == "common_info")
        {
            m_localTcpIP    = (u32)::inet_addr(tokens[1].c_str());
            m_localTcpPort  = (u16)StringToInt(tokens[2]);
        }
        if (tokens[0] == "add_common_server")
        {
            if (tokens.size() < 3)
                continue;

            u32& serverIdx = g_pApp->m_commonServerCount;
            if (tokens[1] == "LOGON")
            {
                g_pApp->m_aCommonServerList[serverIdx].m_connIP     = (u32)::inet_addr(tokens[2].c_str());
                g_pApp->m_aCommonServerList[serverIdx].m_type       = ASC_SERVER_LOGON;
                serverIdx++;
            }
            if (tokens[1] == "TRANS")
            {
                g_pApp->m_aCommonServerList[serverIdx].m_connIP     = (u32)::inet_addr(tokens[2].c_str());
                g_pApp->m_aCommonServerList[serverIdx].m_type       = ASC_SERVER_TRANS;
                serverIdx++;
            }
            if (tokens[1] == "MESSENGER")
            {
                g_pApp->m_aCommonServerList[serverIdx].m_connIP     = (u32)::inet_addr(tokens[2].c_str());
                g_pApp->m_aCommonServerList[serverIdx].m_type       = ASC_SERVER_MESSENGER;
                serverIdx++;
            }
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