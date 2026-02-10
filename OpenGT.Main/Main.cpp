/*
    8/2/26 - RebillionXX
    OpenGT.Main - Main Entry Point

    LEAVE YOUR CREDITS HEERE.
*/

#include <csignal>
#include "App.h"
#include "Common/CommonDef.h"
#include "Logger/LogFileBase.h"

int main(int argc, const char** argv, const char** envp)
{
    g_pApp = new CApp();
    if (!g_pApp)
        return 1;

    if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			g_pApp->AddParm(argv[i]);
		}
	}
    g_pApp->SetupParm();

    g_pLog = new CLogFileA();
    if (!g_pLog || !g_pLog->Create(".gtlogs/opengt_main.txt", 1000))
        return false;

    g_pApp->m_mainLogIdx = g_pLog->AddLogThread("INIT", gettid());

    g_pLog->WriteLog("OpenGT Main V1.0.0");
    g_cachedTick = GetSystemTimeTick();

    if (!g_pApp->Create())
    {
        delete g_pApp;
        return 1;
    }

    g_pLog->WriteLog("Running...");
    
    while (!g_pApp->m_bFrameQuitRequested)
    {
        g_cachedTick = GetSystemTimeTick();

		// PROFILE_BEGIN("MAIN LOOP")
        // g_pApp->LagCheckStart();

        // PROFILE_BEGIN("SLEEP0")
        usleep(1000u);
        // PROFILE_END("SLEEP0")

        // if (!g_sqlIsDown)
            // g_pApp->m_gameServer.Update();

        // UpdateLogCache(false);
        // PROFILE_END("MAIN LOOP")
	}

    return 0;
}