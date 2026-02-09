#include "Logger/LogFileA.h"
#include <cstdarg>
#include "Engine/RingBuffer.h"

struct LOG_FILE_BUFFER
{
    char m_strMessage[LOG_STRING_MAX];
};

CLogFileA::CLogFileA()
{
    m_strFileName[0] = '\0';
}

CLogFileA::~CLogFileA()
{
    Destroy();
}

bool CLogFileA::Create(const char* strFileName, i32 flushTimerDelayMS, i32 logBufferCount)
{
    m_flushTimerDelayMS = flushTimerDelayMS;

    SysMem::FillZero(m_ppLogBuffer, sizeof(m_ppLogBuffer));
    SysText::Copy(m_strFileName, strFileName, LOG_STRING_MAX);

    m_pFile = fopen(strFileName, "a+");
    if (!m_pFile)
        return false;

    return CLogFileBase::Create(logBufferCount);
}

void CLogFileA::Destroy()
{
    //
}

i32 CLogFileA::AddLogThread(const char* strPreString, i32 threadID)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    i32 result = FindWorkIdx(threadID);
    if (result != -1)
        return result;

    if (m_workCounter >= LOG_BUFFER_MAX_COUNTER)
        return -1;

    m_ppLogBuffer[m_workCounter] = new CRingBuffer();
    if (m_ppLogBuffer[m_workCounter] == NULL)
        return -1;

    if (m_ppLogBuffer[m_workCounter]->Create(sizeof(LOG_FILE_BUFFER), m_bufferCount) == false)
    {
        delete m_ppLogBuffer[m_workCounter];
        return -1;
    }

    SysText::Copy(m_aStrLogInit[m_workCounter], strPreString, LOG_INIT_STRING_COUNT);
    result = m_workCounter;

    m_aThreadID[m_workCounter] = threadID;
    m_workCounter++;

    return result;
}

void CLogFileA::WriteLog(const char* strLog, ... )
{
    char buffer[LOG_STRING_MAX];
    memset((void*)buffer, 0, sizeof(buffer));

    va_list marker;
    va_start(marker, strLog);
    vsnprintf(buffer, LOG_STRING_MAX, strLog, marker);
    va_end(marker);

	PushLog(buffer);
}

// TODO: FlushTimerDelayMS - RebillionXX
bool CLogFileA::UpdateLog()
{
    i32 logCount;
    LOG_FILE_BUFFER* pLogBuffer;

    bool bWorking = false;

    for (u32 j = 0; j < m_workCounter; j++)
    {
        logCount = m_ppLogBuffer[j]->GetBufferCount();
        for (i32 i = 0; i < logCount; i++)
        {
            pLogBuffer = (LOG_FILE_BUFFER*)m_ppLogBuffer[j]->Pop();

            WriteLogFile(pLogBuffer->m_strMessage);

            m_ppLogBuffer[j]->PopIdx();

            bWorking = true;
        }
    }

	return bWorking;
}

void CLogFileA::WriteLogFile(char* strLog)
{
    i32 length = (i32)SysText::Length(strLog);
    fwrite(strLog, length, 1, m_pFile);

#ifdef _DEBUG
    printf("%s", strLog);
#endif
}

void CLogFileA::PushLog(char* strLog)
{
    i32 workIdx = FindWorkIdx();
    if (workIdx == -1)
    {
#ifdef _DEBUG
        assert("Invalid Thread ID");
#endif
        return;
    }

    // Setup Pre-String Log
    CRingBuffer*        pRingBuffer = m_ppLogBuffer[workIdx];
    LOG_FILE_BUFFER*    pLogBuffer  = (LOG_FILE_BUFFER*)pRingBuffer->PushPointer();

    if (pLogBuffer != NULL)
    {
        i32 mon, day, year, hour, min, sec;
        GetDateAndTime(&mon, &day, &year, &hour, &min, &sec);

        SysText::Format(pLogBuffer->m_strMessage, LOG_STRING_MAX, "[%02d:%02d:%02d][%s] %s\r\n", hour, min, sec, m_aStrLogInit[workIdx], strLog);
        pRingBuffer->PushPointerIdx();
    }
}