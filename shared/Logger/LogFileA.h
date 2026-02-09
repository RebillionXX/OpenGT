#pragma once
#include "Logger/LogFileBase.h"

// TCHAR / A

class CLogFileA : public CLogFileBase
{
private:
    // Delay in milliseconds between automatic flushes of the log queue
    i32 m_flushTimerDelayMS;

    // File to save
    char m_strFileName[LOG_STRING_MAX];

    // Logs pre-string before flushing messages
    char m_aStrLogInit[LOG_BUFFER_MAX_COUNTER][LOG_INIT_STRING_COUNT];

private:
    void WriteLogFile(char* strLog);
    void PushLog(char* strLog);

protected:
    bool UpdateLog() override;

public:
    CLogFileA();
    ~CLogFileA();

    bool Create(const char* strFileName, i32 flushTimerDelayMS, i32 logBufferCount = 1000);
    void Destroy();

    i32 AddLogThread(const char* strPreString, i32 threadID);

    void WriteLog(const char* strLog, ...);
};