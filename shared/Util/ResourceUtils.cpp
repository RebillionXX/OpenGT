#include "Util/ResourceUtils.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdarg>

void SysMem::Copy(void* pDest, const void* pSrc, u32 sz)
{
	memcpy(pDest, pSrc, (u64)sz);
}

void SysMem::FillZero(void* pDest, u32 sz)
{
	memset(pDest, 0, sz);
}

void SysMem::Fill(void* pDest, i32 num, u32 sz)
{
	memset(pDest, num, sz);
}

void SysMem::MemorySerialize(std::string& str, u8* pMem, i32& offsetInOut, bool bWriteToMem)
{
	u16 len;
	if (bWriteToMem)
	{
		len = (u16)str.length();
		memcpy(&pMem[offsetInOut], &len, sizeof(len));
		offsetInOut += sizeof(len);
		memcpy(&pMem[offsetInOut], str.c_str(), len);
	}
	else
	{
		memcpy(&len, &pMem[offsetInOut], sizeof(len));
		offsetInOut += sizeof(len);
		str.resize(len);
		memcpy((void*)str.c_str(), &pMem[offsetInOut], len);
	}
	offsetInOut += len;
}

void SysMem::MemorySerializeStringEncrypted(std::string& num, u8* pMem, i32& offsetInOut, bool bWriteToMem, i32 cryptID, const char* secretCode)
{
	u16 len;
	i32 codeLen = (i32)strlen(secretCode);
	cryptID = cryptID % codeLen;
	if (bWriteToMem)
	{
		len = (u16)num.length();
		memcpy(&pMem[offsetInOut], &len, sizeof(len));
		offsetInOut += sizeof(len);
		for (int i = 0; i < len; i++)
		{
			u8 b = (u8)num.c_str()[i];
			b = b ^ secretCode[cryptID++];
			if (cryptID >= codeLen)
				cryptID = 0;

			pMem[offsetInOut++] = b;
		}
	}
	else
	{
		memcpy(&len, &pMem[offsetInOut], sizeof(len));
		offsetInOut += sizeof(len);
		num.resize(len);
		for (i32 i = 0; i < len; i++)
		{
			u8 b = pMem[offsetInOut++];
			num[i] = b ^ secretCode[cryptID++];
			if (cryptID >= codeLen)
				cryptID = 0;
		}
	}
}

bool SysMem::MemorySerializeStringLarge(std::string& num, u8* pMem, i32& offsetInOut, bool bWriteToMem, u32 maxBytesInPacket)
{
	u32 len;
	if (bWriteToMem)
	{
		len = (u32)num.length();
		if (maxBytesInPacket != 0 && len > (maxBytesInPacket - 4))
			return false;

		memcpy(&pMem[offsetInOut], &len, sizeof(len));
		offsetInOut += sizeof(len);
		memcpy(&pMem[offsetInOut], num.c_str(), len);
	}
	else
	{
		memcpy(&len, &pMem[offsetInOut], sizeof(len));
		offsetInOut += sizeof(len);
		num.resize(len);
		memcpy((void*)num.c_str(), &pMem[offsetInOut], len);
	}

	offsetInOut += len;
	return true;
}

void SysMem::MemorySerializeRaw(u8* pVar, u8* pMem, i32 sizeBytes, i32& offsetInOut, bool bWriteToMem)
{
	if (sizeBytes == 0)
		return;

	if (bWriteToMem)
	{
		memcpy(&pMem[offsetInOut], pVar, sizeBytes);
	}
	else
	{
		memcpy(pVar, &pMem[offsetInOut], sizeBytes);
	}

	offsetInOut += sizeBytes;
}

const char* SysMem::DumpArray(u8* pBuff, i32 dataLength)
{
	static std::string output;
	output.clear();

	const i32 bytesPerLine = 16;

	// Header
	output += "\n";
	// output += "+--------+-------------------------------------------------+----------------+" 	+ "\n";
	// output += "         |  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F |" 					+ "\n";
	// output += "+--------+-------------------------------------------------+----------------+";

	for (i32 i = 0; i < dataLength; i += bytesPerLine)
	{
		// Offset
		std::ostringstream line;
		line << "\n";
		line << std::setw(8) << std::setfill('0') << std::hex << i << '|';

		// Hex bytes
		for (int j = 0; j < bytesPerLine; ++j)
		{
			if (i + j < dataLength)
				line << ' ' << std::setw(2) << std::setfill('0') << std::uppercase
						<< static_cast<int>(pBuff[i + j]);
			else
				line << "   "; // padding for incomplete line
		}

		line << " |";

		// ASCII representation
		for (int j = 0; j < bytesPerLine && (i + j) < dataLength; ++j)
		{
			unsigned char c = pBuff[i + j];
			line << (std::isprint(c) ? static_cast<char>(c) : '.');
		}

		// Pad ASCII if line is incomplete
		int remainder = bytesPerLine - (std::min(bytesPerLine, dataLength - i));
		line << std::string(remainder, ' ');

		line << '|';

		output += line.str();
	}

	// Footer
	// output += "\n" + "+--------+-------------------------------------------------+----------------+";

	return output.c_str();
}

void SysText::Fill(char* pDest, const char* pSrc, i32 destLength)
{
	strncpy(pDest, pSrc, destLength - 1);
	pDest[destLength - 1] = 0;
}

void SysText::Copy(char* pDest, const char* pSrc, i32 destLength)
{
	if (destLength <= 0)
		return;

	while (*pSrc && --destLength > 0)
	{
		*pDest = *pSrc;
		pDest++;
		pSrc++;
	}
	*pDest = 0;
}

void SysText::Copy(wchar_t* pDest, const wchar_t* pSrc, i32 destLength)
{
	if (destLength <= 0)
		return;

	while (*pSrc && --destLength > 0 )
	{
		*pDest = *pSrc;
		pDest++;
		pSrc++;
	}
	*pDest = 0;
}

i32 SysText::Length(const char* pStr)
{
	i32 count = 0;

	while (*pStr)
	{
		count++;
		pStr++;
	}

	return count;
}

i32 SysText::Length(const wchar_t* pStr)
{
	i32 count = 0;

	while (*pStr)
	{
		count++;
		pStr++;
	}

	return count;
}

i32 SysText::Format(char * strDest, i32 length, const char* strFormat, ... )
{
	va_list marker;
	va_start(marker, strFormat);
	i32 result = vsnprintf(strDest, length, strFormat, marker);
	va_end( marker);

	if (result < 0)
	{
		result = length - 1;
	}

	return result;
}