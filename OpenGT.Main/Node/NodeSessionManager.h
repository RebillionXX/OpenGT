#pragma once
#include <vector>

class CNodeSession;
class CNodeSessionManager
{
protected:
    std::vector<CNodeSession*> m_nodesList;

    // Required for server and user connection
    struct timeval m_timeout;
    CNetworkServerSocket m_listener;

public:
    CNodeSessionManager();
    virtual ~CNodeSessionManager();

    virtual bool OnCreate();
    virtual void OnDestroy();
    virtual void OnUpdate();
};

extern CNodeSessionManager* g_pNodeManager;