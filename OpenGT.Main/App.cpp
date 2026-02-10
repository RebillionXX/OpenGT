#include "App.h"

CApp* g_pApp = NULL;
CLogFileA* g_pLog = NULL;

CApp::CApp() : CBaseApp()
{
    m_mainLogIdx    = 0;
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

    return true;
}

void CApp::Destroy()
{
    SAFE_DELETE(g_pConfig);
    
    SAFE_DELETE(g_pLog);
}

void CApp::Update()
{
    //
}

void CApp::SetupParm()
{
    //
}