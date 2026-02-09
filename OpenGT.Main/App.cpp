#include "App.h"

CApp* g_pApp = NULL;

CLogFileA* g_pLog = NULL;

CApp::CApp() : CBaseApp()
{
    m_mainLogIdx    = 0;
}

CApp::~CApp()
{

}

void CApp::SetupParm()
{
    //
}