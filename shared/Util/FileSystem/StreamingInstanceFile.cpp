#include "StreamingInstanceFile.h"

CStreamingInstanceFile::CStreamingInstanceFile() : m_fp(NULL)
{
    //
}

CStreamingInstanceFile::~CStreamingInstanceFile()
{
	Close();
}

void CStreamingInstanceFile::Close()
{
	if (!m_fp)
        return;

    fclose(m_fp);
    m_fp = NULL;
}

bool CStreamingInstanceFile::IsOpened()
{
	return m_fp != NULL;
}

bool CStreamingInstanceFile::Open(std::string file)
{
	Close();

	m_fp = fopen(file.c_str(), "rb"); //rb
	return m_fp != NULL;
}

i32 CStreamingInstanceFile::Read(u8* pBufferOut, i32 maxBytesToRead)
{
	if (!m_fp)
        return 0;

	i32 bytesRead = (i32)fread(pBufferOut, 1, maxBytesToRead, m_fp);
	return bytesRead;
}

i32 CStreamingInstanceFile::Write(u8* pBufferIn, i32 bufferSize)
{
	if (!m_fp)
        return 0;

	i32 bytesWrite = (i32)fwrite(pBufferIn, bufferSize, 1, m_fp);
	return bytesWrite;
}

bool CStreamingInstanceFile::IsFinished()
{
	if (!m_fp) 
        return true;

	return feof(m_fp) != 0;
}

void CStreamingInstanceFile::SeekFromStart(i32 byteCount)
{
	if (!m_fp) 
        return;

	fseek(m_fp, byteCount, SEEK_SET);
}