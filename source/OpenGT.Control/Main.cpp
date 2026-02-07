// 8/2/26 - RebillionXX
// OpenGT.ControlServer - Main Entry Point

#include <csignal>
#include "App.h"

int main(int argc, const char** argv, const char** envp)
{
    g_pApp = new App();
    if (!g_pApp)
        return 1;

    return 0;
}