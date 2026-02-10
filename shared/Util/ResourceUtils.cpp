#include "Util/ResourceUtils.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdarg>

std::string SeparateStringSTL(std::string input, i32 index, char delimiter)
{
	char stInput[4048];
	if (SeparateString(input.c_str(), index, delimiter, stInput))
		return stInput;

	return "";
}

bool SeparateString(const char str[], i32 num, char delimiter, char* result)
{
	size_t sLen = std::strlen(str);
	i32 l = 0;
	i32 c = 0;

	for (u32 k = 0; str[k] != 0; k++)
	{
		if (str[k] == delimiter)
		{
			l++;
			if (l == num + 1)
				break;

			if (k < sLen)
				c = 0;
		}
		if (str[k] != delimiter)
			result[c++] = str[k];
	}
	result[c] = 0;

	if (l < num)
	{
		result[0] = 0;
		return false;
	}
	return true;
}

void StringReplace(const std::string& what, const std::string& with, std::string& in)
{
	size_t pos = 0;
	size_t whatLen = what.length();
	size_t withLen = with.length();
	while ((pos = in.find(what, pos)) != std::string::npos)
	{
		in.replace(pos, whatLen, with);
		pos += withLen;
	}
}

i32 GetFileSize(const std::string& file)
{
	i32 memLength = -1;
	FILE* pFile = fopen(file.c_str(), "r");
	if (pFile)
	{
		fseek(pFile, 0, SEEK_END);
		memLength = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);
		fclose(pFile);
	}
	return memLength;
}

void AppendStringToFile(const std::string& file, const std::string& text)
{
	FILE* pFile = fopen(file.c_str(), "a+");
	if (!pFile)
		return;

	fwrite(text.c_str(), text.size(), 1, pFile);
	fclose(pFile);
}

bool StringFromStartMatches(const std::string& line, const std::string textToMatch)
{
	for (u32 i = 0; i < (u32)textToMatch.size(); i++)
	{
		if (i >= line.length())
			return false;
		if (line[i] != textToMatch[i])
			return false;
	}
	return true;
}

bool StringFromEndMatches(const std::string& line, const std::string textToMatch)
{
	if (line.size() < textToMatch.size())
		return false;

	i32 sizeOfTextToMatch = (i32)strlen(textToMatch.c_str());
	if (strncmp(&(line.c_str()[line.size() - sizeOfTextToMatch]), textToMatch.c_str(), sizeOfTextToMatch) == 0)
		return true;

	return false;
}

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