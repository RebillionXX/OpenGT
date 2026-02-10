#pragma once
#include <cstdint>
#include <string>
#include "PlatformSetup.h"

class CStreamingInstance;
class CFileSystem
{
public:
	CFileSystem();
	virtual ~CFileSystem();

	virtual u8* Get(std::string file, int* pSizeOut) = 0;
	virtual CStreamingInstance* GetStreaming(std::string file, int* pSizeOut) = 0;
	virtual bool FileExists(std::string file) = 0;
	virtual int GetFileSize(std::string file) = 0;
};