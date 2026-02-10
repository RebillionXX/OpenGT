#pragma once
#include "PlatformSetup.h"

class CTextParser 
{
public:
	CTextParser();
	CTextParser(const char* pCharArray);
	CTextParser(const std::string& fName);
	CTextParser(const std::string& fName, bool bAddBasePath);
    
	~CTextParser();
	void Kill();

	bool LoadFile(const std::string& fName, bool bAddBasePath = true);
	bool SaveFile(const std::string& fName, bool bAddBasePath = true);

	bool IsLoaded();
	bool SetupFromMemoryAddress(const char* pCharArray);
	bool SetupFromMemoryAddressRaw(const char* pCharArray, i32 size);
	bool AppendFromMemoryAddress(const char* pCharArray);
	bool AppendFromMemoryAddressRaw(const char* pCharArray, i32 size);
	bool AppendFromString(const std::string lines);

	std::string GetMultipleLineStrings(std::string key, std::string token = "|");
	std::string GetLine(i32 lineNum);

	std::string GetParmString(std::string key, int index, std::string token = "|");
	i32 GetParmInt(std::string key, int index, std::string token = "|");
	f32 GetParmFloat(std::string key, int index, std::string token = "|");

	void AppendString(std::string key, std::string value, std::string token = "|");
	void AppendInt(std::string key, i32 value, std::string token = "|");

	void DeleteLine(i32 lineNum);
	std::string GetAll();
	std::string GetAllRaw();
	i32 GetLineCount();
	std::vector<std::string>& GetLines();

	std::vector<std::string> TokenizeLine(i32 lineNum, std::string token = "|");
	void AppendToFile(FILE* pFile);

	std::string GetParmStringFromLine(i32 lineNum, i32 index, std::string token = "|");
	i32 GetParmIntFromLine(i32 lineNum, i32 index, std::string token = "|");
	f32 GetParmFloatFromLine(i32 lineNum, i32 index, std::string token = "|");
	i64 GetParmLongFromLine(i32 lineNum, i32 index, std::string token = "|");
    
public:
	std::vector<std::string> m_lines;
	i32 m_lastLine;
};