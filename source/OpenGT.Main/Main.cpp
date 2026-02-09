// 8/2/26 - RebillionXX
// OpenGT.Main - Main Entry Point

#include <csignal>
#include "App.h"

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
    
    return 0;
}