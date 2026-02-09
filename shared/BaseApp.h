#pragma once
#include "PlatformSetup.h"

/*
extern u16 	g_basePort;
extern u16 	g_gamePort;
*/

class CBaseApp
{
protected:
    // Command-line parameters passed to the application at startup.
	std::vector<std::string> m_parms;

public:
    // True when a shutdown is requested (via signal)
    // Used to stop the main loop gracefully.
    bool            m_bFrameQuitRequested;

public:
    CBaseApp();
    virtual ~CBaseApp();
    
protected:
    // Called to initialize and register application-specific command-line parameters
    // Must be implemented by derived classes
    virtual void SetupParm() = 0;

public:
    // Returns the total number of stored command-line parameters
    i32 GetParmCount();

    // Returns the most recently added parameter
    std::string GetLastParm();

    // Adds a new command-line parameter
    void AddParm(std::string parm);

    // Checks whether a specific parameter exists
    bool ParmExists(std::string parm);

    // Checks whether a parameter exists and retrieves its associated value (if any)
    // Returns true if found, and outputs the value through pDataOut
    bool ParmExistsWithData(std::string parm, std::string* pDataOut);
};