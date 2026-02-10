#pragma once
#include <sstream>
#include <mutex>
#include <thread>
#include <queue>

#define LOG_INIT_STRING_COUNT		10
#define LOG_BUFFER_MAX_COUNTER		100
#define LOG_STRING_MAX				1024

class CRingBuffer;
class CLogFileBase
{
private:
    // True if the logging thread is currently running
    bool m_bRunning;

protected:
    // Output file stream used to write log entries to disk
    FILE* m_pFile;

    // Queue of log messages waiting to be written to the file
    std::queue<std::string> m_queue;

    // Mutex used to synchronize access to the log queue
    std::mutex m_mutex;

    // Background thread responsible for writing log messages from the queue
    std::thread m_worker;

    // File save buffer.
    CRingBuffer*            m_ppLogBuffer[LOG_BUFFER_MAX_COUNTER];
    i32                     m_aThreadID[LOG_BUFFER_MAX_COUNTER];
    u32                     m_workCounter;
    i32                     m_bufferCount;

private:
    void Update();
    
protected:
    virtual bool UpdateLog(bool bForceUpdate);

    i32 FindWorkIdx();
    i32 FindWorkIdx(i32 threadID);

public:
    CLogFileBase();
    virtual ~CLogFileBase();

    virtual bool Create(i32 logBufferCount);
    virtual void Destroy();
};
