#include "Node/NodeSessionManager.h"
#include "Node/NodeSession.h"

CNodeSessionManager* g_pNodeManager = NULL;

CNodeSessionManager::CNodeSessionManager()
{
    //
}

CNodeSessionManager::~CNodeSessionManager()
{
    OnDestroy();
}

bool CNodeSessionManager::OnCreate()
{
    m_timeout.tv_sec    = 0;
    m_timeout.tv_usec   = 5;
    if (!m_listener.OnCreate(g_pConfig->m_localTcpIP, g_pConfig->m_localTcpPort))
        return false;

    // Since invalid connections may occur, we allocate 3x the number of sessions and keep them waiting.
    CNodeSession* pNode;
    for (u32 i = 0; i < ((g_pApp->GetServerCount() /*+ g_pApp->GetSuperUserCount()*/) * 3); i++)
    {
        pNode = new CNodeSession();
        pNode->m_nodeIdx = i;
        m_nodesList.push_back(pNode);
    }

    return true;
}

void CNodeSessionManager::OnDestroy()
{
    m_listener.OnDestroy();

    CNodeSession* pNode;
    for (i32 i = 0; i < (i32)m_nodesList.size(); i++)
    {
        SAFE_DELETE(pNode);
    }
}

void CNodeSessionManager::OnUpdate()
{
    // 1). Accept Service Nodes.
    u32 addrLength; // socklen_t
    i32 socket;
    struct sockaddr_in sessionAddr;

    addrLength = sizeof(sockaddr_in);
    socket = m_listener.AcceptConnection(&m_timeout, &sessionAddr, &addrLength);
    if (socket != INVALID_SOCKET)
    {
        LOG_TRACE("WE ACCEPTED A SOCKET.");
    }

    // 2). Update Service Nodes.
    // TODO
}