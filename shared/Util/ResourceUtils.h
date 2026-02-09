#pragma once
#include <cstring>

#ifdef _DEBUG
    // Wrap them up with tracking/logging methods :DD

    #define     MEM_ALLOC           	    malloc

    #define     MEM_COPY(dst, src, sz)      SysMem::Copy(dst, src, sz)

#else

    #define     MEM_ALLOC           	    malloc
#endif

namespace SysMem
{
	void Copy(void* pDest, const void* pSrc, u32 sz);

	void FillZero(void* pDest, u32 sz);
	void Fill(void* pDest, i32 num, u32 sz);

    template <typename T>
    void MemorySerialize(T* pVal, u8* pMem, i32& offsetInOut, bool bWriteToMem)
    {
        if (pVal)
        {
            if (bWriteToMem)
            {
                memcpy(&pMem[offsetInOut], pVal, sizeof(T));
            }
            else
            {
                memcpy(pVal, &pMem[offsetInOut], sizeof(T));
            }
        }
        else
        {
            i32 zero = 0;
            if (bWriteToMem)
                memcpy(&pMem[offsetInOut], &zero, sizeof(T));
        }

        offsetInOut += sizeof(T);
    }
    void MemorySerialize(std::string& str, u8* pMem, i32& offsetInOut, bool bWriteToMem);
    void MemorySerializeRaw(u8* pVar, u8* pMem, i32 sizeBytes, i32& offsetInOut, bool bWriteToMem);
    bool MemorySerializeStringLarge(std::string& num, u8* pMem, i32& offsetInOut, bool bWriteToMem, u32 maxBytesInPacket = 0);
    void MemorySerializeStringEncrypted(std::string& num, u8* pMem, i32& offsetInOut, bool bWriteToMem, i32 cryptID, const char* secretCode);

    // Returns Human-readable hex dump string of the given byte array
    const char* DumpArray(u8* pBuff, i32 dataLength);
};

namespace SysText
{
    void Fill(char* pDest, const char* pSrc, i32 destLength);

    void Copy(char* pDest, const char* pSrc, i32 destLength);
	void Copy(wchar_t* pDest, const wchar_t* pSrc, i32 destLength);

    i32 Length(const char* pStr);
    i32 Length(const wchar_t* pStr);

    i32 Format(char* strDest, i32 length, const char* strFormat, ...);
};