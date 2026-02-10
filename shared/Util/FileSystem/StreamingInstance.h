#pragma once
#include <cstdint>
#include <string>
#include "PlatformSetup.h"

class CStreamingInstance 
{
public:
	CStreamingInstance();
	virtual ~CStreamingInstance();

	virtual bool Open(std::string file) = 0;
	virtual bool ReadLineOfText(std::string& textOut);
	virtual bool ReadLineOfText(char* pBuffer, i32 bufferSize);
	virtual bool IsFinished() = 0;
	virtual i32 Read(u8* pBufferOut, i32 maxBytesToRead) = 0;
	virtual i32 Write(u8* pBufferIn, i32 bufferSize) = 0;
	virtual void SeekFromStart(i32 byteCount) = 0;
	
	i32 ReadInt32();
	f32 ReadFloat32();
};