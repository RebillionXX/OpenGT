#pragma once
#include <cstring>

#ifdef _DEBUG
    // Wrap them up with tracking/logging methods :DD

    #define     MEM_ALLOC           	    malloc

    #define     MEM_COPY(dst, src, sz)      SysMem::Copy(dst, src, sz)

#else

    #define     MEM_ALLOC           	    malloc
#endif

/// Splits a string by a delimiter and returns the element at the specified index.
/// @param input The input string to split
/// @param index The zero-based index of the delimiter-separated element to extract
/// @param delimiter The character to use as a separator
/// @return The extracted string element, or empty string if index is out of bounds
std::string SeparateStringSTL(std::string input, i32 index, char delimiter);

/// Splits a string by a delimiter and stores the nth element in a result buffer.
/// @param str The input string to split
/// @param num The zero-based index of the delimiter-separated element to extract
/// @param delimiter The character to use as a separator
/// @param result Output buffer to store the extracted element (must be pre-allocated)
/// @return True if the element at index 'num' was found, false if index is out of bounds
bool SeparateString(const char str[], i32 num, char delimiter, char* result);

/// Replaces all occurrences of a substring with another substring.
/// @param what The substring to search for and replace
/// @param with The replacement substring
/// @param in The string to perform replacements on (modified in-place)
void StringReplace(const std::string& what, const std::string& with, std::string& in);

// Returns: Size of the file in bytes, or -1 if the file cannot be accessed
i32 GetFileSize(const std::string& file);

// Appends the given text to the end of the specified file
// Creates the file if it does not exist
void AppendStringToFile(const std::string& file, const std::string& text);

// Returns: true if the line starts with the specified text
bool StringFromStartMatches(const std::string& line, const std::string textToMatch);

// Returns: true if the line ends with the specified text
bool StringFromEndMatches(const std::string& line, const std::string textToMatch);

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