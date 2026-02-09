#pragma once
#include <string>
#include <sstream>
#include <vector>
#include "PlatformSetup.h"

// Returns true if the string contains only valid ASCII characters
bool IsValidASCII(const std::string& str);

// Converts the given character array to lowercase (in-place)
void ToLowerCase(char* pCharArray);

// Converts the given character array to uppercase (in-place)
void ToUpperCase(char* pCharArray);

// Returns A lowercase copy of the input string
std::string ToLowerCaseString(const std::string& s);

// Returns An uppercase copy of the input string
std::string ToUpperCaseString(const std::string& s);

i32 Random(i32 range);
i32 RandomRange(i32 rangeMin, i32 rangeMax);
f32 RandomRangeFloat(f32 rangeMin, f32 rangeMax);
i32 GiveOrTake(i32 baseNum, i32 modAmount);
i32 ChooseFromPercentTable(i32 count, f32* percents);

template<class C>
std::string ToString(C value)
{
	std::ostringstream o;
	o << value;
	return o.str();
}

i32 StringToInt(const std::string& s);
f32 StringToFloat(const std::string& s);
bool StringToBool(const std::string& s);
u32 StringToColor(const std::string& s);

std::string IntToTime(u32 milliSeconds, bool bTextFormat = false);
std::string IntToTimeSeconds(u32 seconds, bool bTextFormat = false, bool bShowDays = false);

std::vector<std::string> StringTokenize(const std::string& text, const std::string& delimiter);
std::string StripWhiteSpace(const std::string& input);
std::string StripDangerousFromChat(std::string input, bool bAngleBrackets);
std::string StripColorCodes(std::string input);
std::string TrimLeft(const std::string& s, const std::string& t = " \t\r\n");
std::string TrimRight(const std::string& s, const std::string& t = " \t\r\n");
void RemoveExtraSpaces(std::string& input);

std::string PrefixLeading(const std::string& input, u32 leadingCount, std::string leadingChar, std::string insertAfterPrefix);
std::string PostfixLeading(const std::string& input, u32 leadingCount, std::string leadingChar, std::string insertAfterPrefix);

std::string PeekFirstParmString(std::string* pLineOut, const std::string delimiter);
std::string PopFirstParmString(std::string* pLineOut, const std::string delimiter);
i32 PopFirstParmStringAsInt(std::string* pLineOut, const std::string delimiter);
f32 PopFirstParmStringAsFloat(std::string* pLineOut, const std::string delimiter);

std::string GetFileNameFromString(const std::string& path);
std::string GetFileNameWithoutExtension(const std::string fileName);
std::string GetPathFromString(const std::string& path);

std::string GetFileExtension(std::string fName);
void TruncateString(std::string& input, size_t len);
bool IsInString(const std::string& s, const char* search);
bool IsNonDigit(const std::string& s);
bool IsVowel(char c);

std::string HexToString(std::string input);

u32 HashString(const char* str, i32 len);
u32 GetHashOfFile(std::string fName, bool bAddBasePath);