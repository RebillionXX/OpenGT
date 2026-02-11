#include "Logger/LogFileBase.h"
#include <cstdarg>

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
    // Signal the worker thread to stop
    m_bRunning = false;

    // Wait for the worker thread to finish before cleanup
    if (m_worker.joinable())
    {
        m_worker.join();
    }

    // Now safe to cleanup resources
    if (m_pFile)
    {
        fclose(m_pFile);
        m_pFile = NULL;
    }
    
    for (i32 i = 0; i < m_workCounter; i++)
    {
        SAFE_DELETE(m_ppLogBuffer[i]);
    }
}

void CLogFileBase::Update()
{
    bool bWorking;

    m_bRunning = true;

    while (m_bRunning)
    {
        bWorking = UpdateLog(false);
        if (!bWorking)
        {
            usleep(1);
        }
    }
}

bool CLogFileBase::UpdateLog(bool bForceUpdate)
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

void LogMsg(const char* strLog, ...)
{
    char buffer[LOG_STRING_MAX];
    memset((void*)buffer, 0, sizeof(buffer));

    va_list marker;
    va_start(marker, strLog);
    vsnprintf(buffer, LOG_STRING_MAX, strLog, marker);
    va_end(marker);

#ifdef OPENGT_MAIN
    g_pLog->WriteLog(buffer);
#else
    printf("%s\n", buffer);
#endif
}