#include "Util/TextParser.h"
#include "Util/FileSystem/FileManager.h"
#include "Util/MiscUtils.h"
#include "Util/ResourceUtils.h"

CTextParser::CTextParser()
{
    m_lastLine = 0;
}

CTextParser::CTextParser(const char* pCharArray)
{
	m_lastLine = 0;
	SetupFromMemoryAddress(pCharArray);
}

CTextParser::CTextParser(const std::string& fName)
{
	m_lastLine = 0;
	LoadFile(fName);
}

CTextParser::CTextParser(const std::string& fName, bool bAddBasePath)
{
	m_lastLine = 0;
	LoadFile(fName, bAddBasePath);
}

CTextParser::~CTextParser()
{
	Kill();
}

void CTextParser::Kill()
{
	m_lines.clear();
	m_lastLine = 0;
}

bool CTextParser::LoadFile(const std::string& fName, bool bAddBasePath)
{
	Kill();

	CFileInstance f(fName);
	if (!f.IsLoaded())
		return false;

	return SetupFromMemoryAddress(f.GetAsChars());
}

bool CTextParser::SaveFile(const std::string& fName, bool bAddBasePath)
{
	std::string lineFeed = "\r\n";
	std::string file = (bAddBasePath ? GetSavePath() : "") + fName;

	FILE* pFile = fopen(file.c_str(), "wb");
	if (!pFile)
        return false;

	for (i32 i = 0; i < m_lines.size(); i++)
	{
		fwrite(m_lines[i].c_str(), m_lines[i].size(), 1, pFile);
		fwrite(lineFeed.c_str(), lineFeed.size(), 1, pFile);
	}
	
	fclose(pFile);
	return true;
}

bool CTextParser::IsLoaded()
{
	return !m_lines.empty();
}

bool CTextParser::SetupFromMemoryAddress(const char* pCharArray)
{
	m_lines = ::StringTokenize(pCharArray, "\n");

	for (i32 i = 0; i < m_lines.size(); i++)
		::StringReplace("\r", "", m_lines[i]);

	return true;
}

bool CTextParser::SetupFromMemoryAddressRaw(const char* pCharArray, i32 size)
{
	m_lines = ::StringTokenize(pCharArray, "\n");
	return true;
}

bool CTextParser::AppendFromMemoryAddress(const char* pCharArray)
{
	std::vector<std::string> temp = ::StringTokenize(pCharArray, "\n");
	for (i32 i = 0; i < temp.size(); i++)
	{
		StringReplace("\r", "", temp[i]);
		m_lines.push_back(temp[i]);
	}
	return true;
}

bool CTextParser::AppendFromMemoryAddressRaw(const char* pCharArray, i32 size)
{
	std::vector<std::string> temp = ::StringTokenize(pCharArray, "\n");
	for (i32 i = 0; i < temp.size(); i++)
		m_lines.push_back(temp[i]);

	return true;
}

bool CTextParser::AppendFromString(const std::string lines)
{
	std::vector<std::string> temp = ::StringTokenize(lines, "\n");
	for (i32 i = 0; i < temp.size(); i++)
	{
		StringReplace("\r", "", temp[i]);
		m_lines.push_back(temp[i]);
	}
	return true;
}

std::string CTextParser::GetMultipleLineStrings(std::string key, std::string token)
{
	for (u32 i = m_lastLine; i < m_lines.size(); i++)
	{
		if (m_lines[i].empty())
			continue;

		std::vector<std::string> line = StringTokenize(m_lines[i], token);
		if (line[0] != key)
			continue;

		m_lastLine = i + 1;
		return m_lines[i];
	}
	m_lastLine = 0;
	return "";
}

std::string CTextParser::GetLine(i32 lineNum)
{
	if ((i32)m_lines.size() > lineNum && lineNum >= 0)
	{
		return m_lines[lineNum];
	}

	return "";
}

std::string CTextParser::GetParmString(std::string key, i32 index, std::string token)
{
	if (m_lines.empty() || token.empty())
		return "";

	for (i32 i = 0; i < m_lines.size(); i++)
	{
		if (m_lines[i].empty())
			continue;

		std::vector<std::string> line = ::StringTokenize(m_lines[i], token);
		if (line[0] == key)
			return line[index];
	}

	return "";
}

i32 CTextParser::GetParmInt(std::string key, i32 index, std::string token)
{
	return atoi(GetParmString(key, index, token).c_str());
}

f32 CTextParser::GetParmFloat(std::string key, i32 index, std::string token)
{
	return (f32)atof(GetParmString(key, index, token).c_str());
}

void CTextParser::AppendString(std::string key, std::string value, std::string token)
{
	m_lines.push_back(key + token + value);
}

void CTextParser::AppendInt(std::string key, i32 value, std::string token)
{
	AppendString(key, std::to_string(value), token);
}

void CTextParser::DeleteLine(i32 lineNum)
{
	if (m_lastLine && m_lastLine >= lineNum)
		m_lastLine--;

	m_lines.erase(m_lines.begin() + lineNum);
}

std::string CTextParser::GetAll()
{
	std::string s;

	for (int i = 0; i < m_lines.size(); i++)
		s += ::StripWhiteSpace(m_lines[i]) + "\n";

	return s;
}

std::string CTextParser::GetAllRaw()
{
	std::string s;

	for (int i=0; i < m_lines.size(); i++)
		s += m_lines[i] + "\n";

	return s;
}

i32 CTextParser::GetLineCount()
{ 
	return (i32)m_lines.size();
}

std::vector<std::string>& CTextParser::GetLines()
{
	return m_lines;
}

std::vector<std::string> CTextParser::TokenizeLine(i32 lineNum, std::string token)
{
	return StringTokenize(m_lines[lineNum], token);
}

void CTextParser::AppendToFile(FILE* pFile)
{
	if (m_lines.empty() || !pFile)
		return;

	std::string temp;
	for (i32 i = 0; i < (i32)m_lines.size(); i++)
	{
		temp = m_lines[i] + "\r\n";
		fwrite(temp.c_str(), temp.size(), 1, pFile);
	}
}

std::string CTextParser::GetParmStringFromLine(i32 lineNum, i32 index, std::string token)
{
	// assert(lineNum >= 0 && (uint32)lineNum < m_lines.size());
	// assert(token.size() == 1 && "We don't actually support a non char delim yet");
	return SeparateStringSTL(m_lines[lineNum], index, token[0]);
}

i32 CTextParser::GetParmIntFromLine(i32 lineNum, i32 index, std::string token)
{
	// assert(lineNum >= 0 && (uint32)lineNum < m_lines.size());
	// assert(token.size() == 1 && "We don't actually support a non char delim yet");
	return atoi(SeparateStringSTL(m_lines[lineNum], index, token[0]).c_str());
}

f32 CTextParser::GetParmFloatFromLine(i32 lineNum, i32 index, std::string token)
{
	// assert(lineNum >= 0 && (uint32)lineNum < m_lines.size());
	// assert(token.size() == 1 && "We don't actually support a non char delim yet");
	return (f32)atof(SeparateStringSTL(m_lines[lineNum], index, token[0]).c_str());
}

i64 CTextParser::GetParmLongFromLine(i32 lineNum, i32 index, std::string token)
{
	// assert(lineNum >= 0 && (uint32)lineNum < m_lines.size());
	// assert(token.size() == 1 && "We don't actually support a non char delim yet");
	return atol(SeparateStringSTL(m_lines[lineNum], index, token[0]).c_str());
}