// 8/2/26 - RebillionXX
// OpenGT.Main - Main Entry Point

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

    g_pLog = new CLogFileBase();
    
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