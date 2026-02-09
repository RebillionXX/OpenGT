#include "BaseApp.h"

CBaseApp::CBaseApp()
{
    m_parms = std::vector<std::string>();
    m_bFrameQuitRequested = false;
}

CBaseApp::~CBaseApp()
{
    //
}

i32 CBaseApp::GetParmCount()
{
    return (i32)m_parms.size();
}

std::string CBaseApp::GetLastParm()
{
    return m_parms.back();
}

void CBaseApp::AddParm(std::string parm)
{
    m_parms.push_back(parm);
}

bool CBaseApp::ParmExists(std::string parm)
{
	for (i32 i = 0; i < (i32)m_parms.size(); i++)
	{
		if (ToLowerCaseString(parm) != ToLowerCaseString(m_parms[i]))
            continue;

        return true;
	}
	return false;
}

bool CBaseApp::ParmExistsWithData(std::string parm, std::string* pDataOut)
{
	for (i32 i = 0; i < (i32)m_parms.size(); i++)
	{
		if (ToLowerCaseString(parm) != ToLowerCaseString(m_parms[i]))
            continue;
        
        if (i >= m_parms.size())
            return false;

        *pDataOut = m_parms[i + 1];
        return true;
	}
	return false;
}