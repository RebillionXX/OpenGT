#include "Logger/LogFileBase.h"

CLogFileBase::CLogFileBase()
{
    //
}

CLogFileBase::~CLogFileBase()
{
    Destroy();
}

bool CLogFileBase::Create(const char* pStrFileName, i32 flushTimerDelayMS)
{
    m_flushTimerDelayMS = flushTimerDelayMS;
    m_pFile = fopen(pStrFileName, "a+");
    if (!m_pFile)
        return false;

    // Start the background log flushing thread :DD
    m_worker = std::thread([this]()
    {
        this->Update();
    });

    return true;
}

void CLogFileBase::Destroy()
{    
    m_bRunning = false;

    if (m_pFile)
    {
        fclose(m_pFile);
    }

    m_pFile = NULL;
}

void CLogFileBase::Update()
{
    bool bWorking;

    m_bRunning = true;

    while (m_bRunning)
    {
        bWorking = UpdateLog();
        if (!bWorking)
        {
            usleep(1);
        }
    }
}

bool CLogFileBase::UpdateLog()
{
    return false;
}