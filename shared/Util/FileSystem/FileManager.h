#pragma once 
#include "FileSystem.h"
#include <list>

class CFileSystem;
class CStreamingInstance;
class CFileInstance
{
public:
	CFileInstance();
	CFileInstance(const std::string& fName);
	CFileInstance(const std::string& fName, bool bAddBasePath);
	~CFileInstance();

	bool Load(std::string fName, bool bAddBasePath = true);

	bool IsLoaded();
	u8* GetAsBytes();
	char* GetAsChars();
	i32 GetSize();

private:	
	void Kill();

	u8* m_pData;
	i32 m_size;
};

class CFileManager
{
public:
	CFileManager();
	virtual ~CFileManager();

	u8* Get(std::string file, i32* pSizeOut, bool bAddBasePath = true, bool bAutoDecompress = true);
	CStreamingInstance* GetStreaming(std::string file, i32* pSizeOut);
	void MountFileSystem(CFileSystem* pFileSystem);
	bool FileExists(std::string file);
	i32 GetFileSize(std::string file);
	CFileSystem* GetFileSystem(i32 index);
	bool Copy(std::string srcFile, std::string dstFile);

private:
	std::list<CFileSystem*> m_fileSystems;
};

CFileManager* GetFileManager();