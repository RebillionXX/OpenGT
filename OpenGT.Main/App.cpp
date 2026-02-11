#include "App.h"
#include "Node/NodeSession.h"
#include "Node/NodeSessionManager.h"

CApp* g_pApp = NULL;
CLogFileA* g_pLog = NULL;

CApp::CApp() : CBaseApp()
{
    m_mainLogIdx            = 0;

    m_commonServerCount     = 0;
    SysMem::FillZero(m_aCommonServerList, sizeof(SERVER_INFO_COMMON) * ASC_SERVER_COUNT);
}

CApp::~CApp()
{
    Destroy();
}

bool CApp::Create()
{
    g_pConfig = new CMainConfig();
    if (!g_pConfig || !g_pConfig->Load("./main_config.txt"))
    {
        g_pLog->WriteLog("[ERROR] Failed to load config file.");
        return false;
    }

    g_pNodeManager = new CNodeSessionManager();
    if (!g_pNodeManager || !g_pNodeManager->OnCreate())
    {
        g_pLog->WriteLog("[ERROR] Failed to create NodeSessionManager.");
        return false;
    }

    return true;
}

void CApp::Destroy()
{
    SAFE_DELETE(g_pNodeManager);
    SAFE_DELETE(g_pConfig);
    
    SAFE_DELETE(g_pLog);
}

void CApp::Update()
{
    g_pNodeManager->OnUpdate();
}

void CApp::SetupParm()
{
    //
}