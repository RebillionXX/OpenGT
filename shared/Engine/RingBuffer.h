#pragma once

enum RING_BUFFER_RESULT
{
	RING_BUFFER_SUCCESS					= 0x00000000,
	RING_BUFFER_ERROR_BUFFER_FULLIDX	= 0x80000001,
	RING_BUFFER_ERROR_BUFFER_FULL		= 0x80000002,
};

/*
In order to create a stable design, two threads are used:
1. Write
2. Read
When performing these operations, we do not use a Critical Section
and instead control access using a buffer.
*/

class CRingBuffer
{
protected:
    // Size of each buffer block in bytes
    u32 m_bufferSize;

    // Total number of buffer blocks.
    u32 m_bufferCount;

    // Current write index in the buffer (volatile for thread-safety)
    volatile u32 m_writeIdx;

    // Current read index in the buffer (volatile for thread-safety)
    volatile u32 m_readIdx;

    // Pointer to the raw memory block storing all buffers
    // The total allocated size is (m_bufferSize * m_bufferCount) bytes
    char* m_pBuffer;

public:
	CRingBuffer(); 
	virtual ~CRingBuffer(); 

    // Creates the ring buffer with the given block size and count
    bool Create(i32 bufferSize, i32 bufferCount); 
    bool Destroy();

    // Returns: Number of unused buffer blocks available for writing
    u32 GetEmptyBufferCount();

    // Returns: Number of buffer blocks currently holding data
    u32 GetBufferCount();

    // =============================================== //
    // ================== Data Save ================== //
    // =============================================== //

    // Pushes data into the next available buffer block
    // Returns: RING_BUFFER_RESULT
    i32 Push(void* pBuffer);

    // Pushes data of given size into the next available buffer block
    // Returns: RING_BUFFER_RESULT
    i32 Push(void* pBuffer, i32 size);

    // Returns: pointer to the next writable buffer block
    void* PushPointer();

    // Moves the write index forward after using PushPointer()
    void PushPointerIdx();

    // =============================================== //
    // ================== Data Load ================== //
    // =============================================== //

    // Returns: pointer to the next readable buffer block, or nullptr if empty
    void* Pop();

    // Moves the read index forward after using Pop()
    void PopIdx();
};
