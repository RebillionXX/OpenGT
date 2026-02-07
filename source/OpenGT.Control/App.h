#pragma once

class App
{
private:
    //
    
public:
    // True when a shutdown is requested (via signal)
    // Used to stop the main loop gracefully.
    bool m_bFrameQuitRequested;

public:
    App();
    virtual ~App();
};

extern App* g_pApp;