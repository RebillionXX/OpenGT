#pragma once
#include <sstream>
#include <mutex>
#include <thread>
#include <queue>

class CLogFileBase
{
private:
    // True if the logging thread is currently running
    bool m_bRunning;

    // Delay in milliseconds between automatic flushes of the log queue
    i32 m_flushTimerDelayMS;

    // Output file stream used to write log entries to disk
    FILE* m_pFile;

    // Queue of log messages waiting to be written to the file
    std::queue<std::string> m_queue;

    // Mutex used to synchronize access to the log queue
    std::mutex m_mutex;

    // Background thread responsible for writing log messages from the queue
    std::thread m_worker;

private:
    void Update();
    
protected:
    virtual bool UpdateLog();

public:
    CLogFileBase();
    virtual ~CLogFileBase();

    virtual bool Create(const char* pStrFileName, i32 flushTimerDelayMS);
    virtual void Destroy();
};
