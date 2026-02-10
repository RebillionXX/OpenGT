#include "Util/MiscUtils.h"


bool IsValidASCII(const std::string& str)
{
	for (char ch : str)
	{
		if (!std::isalnum(ch))
			return false;
	}
	return true;
}

void ToLowerCase(char* pCharArray)
{
	for (i32 i = 0; pCharArray[i]; i++)
	{
		pCharArray[i] = tolower(pCharArray[i]);
	}
}

void ToUpperCase(char* pCharArray)
{
	for (i32 i = 0; pCharArray[i]; i++)
	{
		pCharArray[i] = toupper(pCharArray[i]);
	}
}

std::string ToLowerCaseString(const std::string& s)
{
	std::string d(s);
	for (u32 i = 0; i < d.length(); i++)
	{
		d[i] = tolower(d[i]);
	}
	return d;
}

std::string ToUpperCaseString(const std::string& s)
{
	std::string d(s);
	for (u32 i = 0; i < d.length(); i++)
	{
		d[i] = toupper(d[i]);
	}
	return d;
}

i32 Random(i32 range)
{
	if (range == 0)
		return 0;

	return rand() % range;
}

i32 RandomRange(i32 rangeMin, i32 rangeMax)
{
	if (rangeMin == rangeMax)
		return rangeMin;

	return rand() % (rangeMax - rangeMin) + rangeMin;
}

f32 RandomRangeFloat(f32 rangeMin, f32 rangeMax)
{
	f32 random = ((f32)rand()) / (f32)RAND_MAX;
	f32 diff = rangeMax - rangeMin;
	f32 r = random * diff;
	return rangeMin + r;
}

i32 GiveOrTake(i32 baseNum, i32 modAmount)
{
	if (modAmount == 0)
		return baseNum;

	return baseNum + (Random(modAmount * 2) - modAmount);
}

i32 ChooseFromPercentTable(i32 count, f32* percents)
{
	if (count <= 0 || !percents)
		return -1;

	f32 randIdx = RandomRangeFloat(0.0f, 100.0f); // random number 0..100
	f32 sum = 0.0f;

	for (i32 i = 0; i < count; i++)
	{
		sum += percents[i];
		if (randIdx >= sum)
			continue;

		return i;
	}

	return count - 1;
}

i32 StringToInt(const std::string& s)
{
	return atoi(s.c_str());
}

f32 StringToFloat(const std::string& s)
{
	return (f32)atof(s.c_str());
}

bool StringToBool(const std::string& s)
{
	std::string fmt = ToLowerCaseString(s);
	if (fmt == "true" || fmt == "1" || fmt == "yes")
		return true;

	return false;
}

u32 StringToColor(const std::string& s)
{
	std::vector<std::string> tokens = StringTokenize(s, ",");
	if (tokens.size() != 4)
		return 0;

	u8 r = (u8)StringToInt(tokens[0]);
	u8 g = (u8)StringToInt(tokens[1]);
	u8 b = (u8)StringToInt(tokens[2]);
	u8 a = (u8)StringToInt(tokens[3]);

	return MAKE_RGBA(r, g, b, a);
}

std::string IntToTime(u32 milliSeconds, bool bTextFormat)
{
	return IntToTimeSeconds(milliSeconds / 1000, bTextFormat);
}

std::string IntToTimeSeconds(u32 seconds, bool bTextFormat, bool bShowDays)
{
	u32 originalSeconds = seconds;

	u32 minutes = seconds / 60;
	seconds -= minutes * 60;

	u32 hours = minutes / 60;
	minutes -= hours * 60;

	u32 days = hours / 24;
	hours -= days * 24;

	std::string result;

	if (!bTextFormat)
	{
		char tmp[24];
		if (hours > 0 || days > 0)
		{
			if (bShowDays)
				sprintf(tmp, "%d:%02d:%02d", days, hours, minutes);
			else
				sprintf(tmp, "%d:%02d:%02d", hours + (days * 24), minutes, seconds);

		}
		else
		{
			sprintf(tmp, "%d:%02d", minutes, seconds);
		}

		return std::string(tmp);
	}

	if (originalSeconds <= 0)
		return "None";

	if (seconds > 0)
	{
		result += ToString(seconds) + " secs";
	}

	if (minutes > 0)
	{
		if (!result.empty())
		{
			result = ", " + result;
		}

		std::string tmp = " mins";
		if (minutes == 1)
		{
			tmp = " min";
		}

		result = ToString(minutes) + tmp + result;

	}

	if (hours > 0)
	{
		if (!result.empty())
		{
			result = ", " + result;
		}

		std::string tmp = " hours";
		if (hours == 1)
		{
			tmp = " hour";
		}

		result = ToString(hours) + tmp + result;
	}

	if (days > 0)
	{
		if (!result.empty())
		{
			result = ", " + result;
		}

		std::string tmp = " days";
		if (days == 1)
		{
			tmp = " day";
		}

		result = ToString(days) + tmp + result;
	}

	return (result.empty() ? "Now!" : result);
}

std::vector<std::string> StringTokenize(const std::string& text, const std::string& delimiter)
{
	std::vector<std::string> result;
	if (text.empty())
		return result;

	size_t start = 0, end = 0;
	while (end != std::string::npos)
	{
		end = text.find(delimiter, start);
		result.push_back(text.substr(start, (end == std::string::npos) ? std::string::npos : end - start));
		start = ((end > (std::string::npos - delimiter.size())) ? std::string::npos : end + delimiter.size());
	}

	return result;
}

std::string StripWhiteSpace(const std::string& input)
{
	std::string d(input);
	return TrimLeft(TrimRight(d, " \t\r\n"), " \t\r\n");
}

std::string TrimLeft(const std::string& s, const std::string& t)
{
	std::string d(s);
	return d.erase(0, s.find_first_not_of(t));
}

std::string TrimRight(const std::string& s, const std::string& t)
{
	std::string d(s);
	std::string::size_type i(d.find_last_not_of(t));
	if (i == std::string::npos)
		return "";

	return d.erase(i + 1);
}