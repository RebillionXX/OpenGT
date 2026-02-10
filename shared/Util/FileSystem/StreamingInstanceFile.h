#pragma once
#include "StreamingInstance.h"

class CStreamingInstanceFile : public CStreamingInstance
{
private:
	FILE* m_fp;

public:
	CStreamingInstanceFile();
	virtual ~CStreamingInstanceFile();

	bool IsOpened();

	virtual bool Open(std::string file);
	virtual bool IsFinished();
	virtual i32 Read(u8* pBufferOut, i32 maxBytesToRead);
	virtual i32 Write(u8* pBufferIn, i32 bufferSize);
	virtual void Close();
	virtual void SeekFromStart(i32 byteCount);
};