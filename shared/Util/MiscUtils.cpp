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