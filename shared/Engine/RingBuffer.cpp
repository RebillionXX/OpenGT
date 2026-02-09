#include "Engine/RingBuffer.h"

#define BUFFER_MAX_INT_COUNT			2000000000
// #define BUFFER_MAX_INT_COUNT			4000000000

CRingBuffer::CRingBuffer()
{
    m_pBuffer			= NULL; 
    m_writeIdx		    = 0;
    m_readIdx		    = 0;
    m_bufferSize	    = 0;
    m_bufferCount	    = 0;
}

CRingBuffer::~CRingBuffer()
{
    Destroy(); 
}

bool CRingBuffer::Create(i32 bufferSize, i32 bufferCount)
{
    m_writeIdx		= 0;
    m_readIdx		= 0;
    m_bufferSize	= bufferSize;
    m_bufferCount	= bufferCount;

    m_pBuffer = new char[bufferSize * bufferCount];
    if (m_pBuffer == NULL)
        return false; 

    return true; 
}

bool CRingBuffer::Destroy()
{
    SAFE_DELETE_ARRAY(m_pBuffer);
    return true; 
}

u32 CRingBuffer::GetEmptyBufferCount()
{	
    return m_bufferCount - GetBufferCount();
}

u32 CRingBuffer::GetBufferCount()
{
    u32 result = 0;
    if (m_writeIdx > m_readIdx)
    {
        result = m_writeIdx - m_readIdx;
    }
    return result;
}

i32 CRingBuffer::Push(void* pBuffer)
{
	return Push(pBuffer, m_bufferSize);
}

i32 CRingBuffer::Push(void* pBuffer, i32 size)
{
    if (m_writeIdx > (BUFFER_MAX_INT_COUNT - 100))
    {
        if (m_writeIdx == m_readIdx)
        {
            m_writeIdx	= 0;
            m_readIdx	= 0;
        }
    }

    if (m_readIdx > BUFFER_MAX_INT_COUNT)
        return RING_BUFFER_ERROR_BUFFER_FULLIDX;

    if ((m_writeIdx - m_readIdx) >= m_bufferCount)
        return RING_BUFFER_ERROR_BUFFER_FULL;

    i32 curWriteIdx = m_writeIdx % m_bufferCount; 
    memcpy(&m_pBuffer[curWriteIdx * m_bufferSize], pBuffer, size);
    // S2Memory::Copy( &m_pBuffer[iWriteIdx * m_bufferSize], pBuffer, i32Size); 

    m_writeIdx++;
    return RING_BUFFER_SUCCESS; 
}

void* CRingBuffer::PushPointer()
{
    if (m_writeIdx > (BUFFER_MAX_INT_COUNT - 100))
    {
        if (m_writeIdx == m_readIdx)
        {
            m_writeIdx	= 0;
            m_readIdx	= 0;
        }
    }

    if (m_readIdx > BUFFER_MAX_INT_COUNT)
        return NULL;
    if ((m_writeIdx - m_readIdx) >= m_bufferCount)
        return NULL;

    i32 curWriteIdx = m_writeIdx % m_bufferCount; 
    return &m_pBuffer[curWriteIdx * m_bufferSize]; 
}

void CRingBuffer::PushPointerIdx()
{
    m_writeIdx++;
}

void* CRingBuffer::Pop()
{
    void* pBuffer = NULL; 

    if (GetBufferCount() > 0)
    {
        i32 curReadIdx = m_readIdx % m_bufferCount; 
        pBuffer = &m_pBuffer[curReadIdx * m_bufferSize]; 
    }

    return pBuffer; 
}

void CRingBuffer::PopIdx()
{
	if (GetBufferCount() > 0)
        m_readIdx++;
}