#include "FileManager.h"
#include "FileSystem.h"
#include "StreamingInstanceFile.h"
#include "Util/MiscUtils.h"
#include "Util/ResourceUtils.h"

CFileManager g_fileManager;
CFileManager* GetFileManager()
{
	return &g_fileManager;
}

CFileInstance::CFileInstance()
{
	m_size = 0;
	m_pData = NULL;
}

CFileInstance::CFileInstance(const std::string& fName) : m_pData(NULL)
{
	Load(fName);
}

CFileInstance::CFileInstance(const std::string& fName, bool bAddBasePath) : m_pData(NULL)
{
	Load(fName, bAddBasePath);
}

void CFileInstance::Kill()
{
	if (m_pData)
		delete m_pData;

	m_size = 0;
}

CFileInstance::~CFileInstance()
{
	Kill();
}

bool CFileInstance::Load(std::string fName, bool bAddBasePath)
{
	Kill();
	m_pData = GetFileManager()->Get(fName, &m_size);
	return IsLoaded();
}

bool CFileInstance::IsLoaded()
{
	return m_pData != NULL;
}

u8* CFileInstance::GetAsBytes()
{
	return m_pData;
}

char* CFileInstance::GetAsChars()
{
	return (char*)m_pData;
}

i32 CFileInstance::GetSize()
{
	return m_size;
}

CFileManager::CFileManager()
{
    //
}

CFileManager::~CFileManager()
{
	std::list<CFileSystem*>::iterator itor = m_fileSystems.begin();
	while (!m_fileSystems.empty())
	{
		CFileSystem* pFileSystem = *m_fileSystems.begin();
		m_fileSystems.pop_front();
		delete pFileSystem;
	}
}

u8* CFileManager::Get(std::string file, i32* pSizeOut, bool bAddBasePath, bool bAutoDecompress)
{	
    u8* pData = NULL;
    std::list<CFileSystem*>::reverse_iterator itor = m_fileSystems.rbegin();

    while (itor != m_fileSystems.rend())
	{
        pData = (*itor)->Get(file, pSizeOut);
        if (pData)
			break;

        itor++;
    }

    if (!pData)
    {
		if (bAddBasePath)
		{
			file = GetAppPath() + file;
		}

        FILE* fp = fopen(file.c_str(), "rb");
        if (!fp)
            return NULL;

        fseek(fp, 0, SEEK_END);
        *pSizeOut = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        pData = (u8*)new u8[((*pSizeOut) +1)];
        if (!pData)
            return 0;
        
        pData[*pSizeOut] = 0; 
        size_t temp = fread(pData, *pSizeOut, 1, fp);
        fclose(fp);
    }

    /*
    if (bAutoDecompress && IsAPackedFile(pData)) {
        unsigned int decompressedSize;
        uint8_t* pDecompressedData = DecompressRTPackToMemory(pData, &decompressedSize);
        *pSizeOut = decompressedSize;
        SAFE_DELETE_ARRAY(pData);
        return pDecompressedData;
    }*/

    return pData;
}

CStreamingInstance* CFileManager::GetStreaming(std::string file, i32* pSizeOut)
{
	CStreamingInstance* pStreaming = NULL;
	std::list<CFileSystem*>::reverse_iterator itor = m_fileSystems.rbegin();

	while (itor != m_fileSystems.rend())
	{
		pStreaming = (*itor)->GetStreaming(file, pSizeOut);
		if (pStreaming)
			return pStreaming;

        itor++;
	}

	CStreamingInstanceFile* pStreamingFile = new CStreamingInstanceFile();
	if (!pStreamingFile->Open(file))
	{ 
		delete pStreamingFile;
		return NULL;
	}

	return pStreamingFile;
}

void CFileManager::MountFileSystem(CFileSystem* pFileSystem)
{
	m_fileSystems.push_back(pFileSystem);
}

bool CFileManager::FileExists(std::string file)
{
	std::list<CFileSystem*>::reverse_iterator itor = m_fileSystems.rbegin();

	while (itor != m_fileSystems.rend())
	{
		if ((*itor)->FileExists(file))
			return true;

		itor++;
    }

	FILE *fp = fopen((file).c_str(), "rb");
	if (!fp)	
		return false;

	fclose(fp);
	return true;
}

i32 CFileManager::GetFileSize(std::string file)
{
	std::list<CFileSystem*>::reverse_iterator itor = m_fileSystems.rbegin();

	while (itor != m_fileSystems.rend())
	{
		i32 fileSize = ((*itor)->GetFileSize(file));
		if (fileSize >= 0)
			return fileSize;

		itor++;
	}

	return ::GetFileSize(file);
}

CFileSystem* CFileManager::GetFileSystem(i32 index)
{
	if (index < 0 || index > (i32)m_fileSystems.size())
        return 0;

	std::list<CFileSystem*>::iterator itor = m_fileSystems.begin();

	i32 count = 0;
	while (itor != m_fileSystems.end())
	{
		if (count++ == index)
			return (*itor);

		itor++;
	}

	return NULL;
}

bool CFileManager::Copy(std::string srcFile, std::string dstFile)
{
	i32 size;
	CStreamingInstance* pSrc = GetFileManager()->GetStreaming(srcFile, &size);
	if (!pSrc)
        return false;

	const i32 bufferSize = 512;
	u8 buffer[bufferSize];

	FILE* fp = fopen(dstFile.c_str(), "wb");
	if (!fp)
	{
		delete pSrc;
		return false;
	}

	while (!pSrc->IsFinished())
	{
		int bytesRead = pSrc->Read(buffer, bufferSize);
		if (bytesRead > 0)
			fwrite(buffer, bytesRead, 1, fp);
	}

	fclose(fp);
	delete pSrc;
	return true;
}
