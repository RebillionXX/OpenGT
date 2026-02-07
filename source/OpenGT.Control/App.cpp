#include "App.h"

App* g_pApp = NULL;

App::App()
{
    m_bFrameQuitRequested = false;
}

App::~App()
{

}