#include "Logger/LogFileBase.h"

CLogFileBase::CLogFileBase()
{
    m_workCounter = 0;
}

CLogFileBase::~CLogFileBase()
{
    Destroy();
}

bool CLogFileBase::Create(i32 logBufferCount)
{
    m_bufferCount           = logBufferCount;

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

    for (u32 i = 0; i < m_workCounter; i++)
    {
        SAFE_DELETE(m_ppLogBuffer[i]);
    }

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

i32 CLogFileBase::FindWorkIdx()
{
    i32 threadID = (i32)gettid();

    for (u32 i = 0; i < m_workCounter; i++)
    {
        if (m_aThreadID[i] != threadID)
            continue;

        return i;
    }

    return -1;
}

i32 CLogFileBase::FindWorkIdx(i32 threadID)
{
    for (u32 i = 0; i < m_workCounter; i++)
    {
        if (m_aThreadID[i] != threadID)
            continue;

        return i;
    }

    return -1;
}