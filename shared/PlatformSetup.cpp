#include "PlatformSetup.h"

std::string GetAppPath()
{
	char szDir[1024];
	if (getcwd(szDir, sizeof(szDir)) == NULL)
		return "/";

	return std::string(szDir) + "/";
}

std::string GetSavePath()
{
	return "";
}

u32 GetSystemTimeTick()
{
	static u32 incrementingTimer = 0;
	static f64 buildUp = 0;
	static f64 lastTime = 0;

	struct timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	f64 timeDouble = time.tv_sec * 1000 + time.tv_nsec / 1000000;

	f64 change = timeDouble - lastTime;
	if (change > 0 && change < (1000 * 120))
	{
		incrementingTimer += change;
	}
	lastTime = timeDouble;

	return incrementingTimer;
}

u64 GetSystemTimeTickLong()
{
	struct timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	u64 accum;
	accum = time.tv_sec * 1000 + time.tv_nsec / 1000000;
	return accum;
}

f64 GetSystemTimeAccurate()
{
	return f64(GetSystemTimeTick());
}

std::string GetTimeAsString()
{
	time_t now;
	time(&now);
	tm* parts = localtime(&now);

	char stTemp[128];
	sprintf(stTemp, "%d:%d:%d", parts->tm_hour, parts->tm_min, parts->tm_sec);
	return std::string(stTemp);
}

std::string GetDateAndTimeAsString()
{
	time_t now;
	time(&now);
	tm* parts = localtime(&now);

	char stTemp[128];
	// sprintf(stTemp, "[%d:%d:%d]", parts->tm_hour, parts->tm_min, parts->tm_sec);
	sprintf(stTemp, "%d/%d %d:%d:%d", parts->tm_mday, parts->tm_mon + 1, parts->tm_hour, parts->tm_min, parts->tm_sec);
	return std::string(stTemp);
}

void GetDateAndTime(i32* monthOut, i32* dayOut, i32* yearOut, i32* hourOut, i32* minOut, i32* secOut)
{
	time_t now;
	time(&now);
	tm* parts = localtime(&now);

	*monthOut = parts->tm_mon + 1;
	*dayOut = parts->tm_mday;
	*yearOut = parts->tm_year + 1900;
	*hourOut = parts->tm_hour;
	*minOut = parts->tm_min;
	*secOut = parts->tm_sec;
}