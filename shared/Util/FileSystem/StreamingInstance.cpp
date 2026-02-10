#include "StreamingInstance.h"

CStreamingInstance::CStreamingInstance()
{
	//
}

CStreamingInstance::~CStreamingInstance()
{
	//
}

bool CStreamingInstance::ReadLineOfText(std::string& textOut)
{
	textOut.clear();

	if (IsFinished())
		return false;

	char buffer[4048];
	i32 cur = 0;

	while(true)
	{
		if (!Read((uint8_t*)&buffer[cur], 1))
		{
			buffer[cur] = 0;
			textOut = buffer;
			return (cur == 0) ? false : true;
		}
		if (buffer[cur] == '\r')
		{
			continue;
		}
		if (buffer[cur] == '\n')
		{
			buffer[cur] = 0;
			textOut = buffer;
			return true;
		}
		cur++;
	}
}

bool CStreamingInstance::ReadLineOfText(char* buffer, i32 bufferSize)
{
	if (IsFinished())
		return false;

	i32 cur = 0;

	while(true)
	{
		if (!Read((u8*)&buffer[cur], 1))
		{
			buffer[cur] = 0;
			return (cur == 0) ? false : true;
		}
		if (buffer[cur] == '\r')
		{
			continue;
		}
		if (buffer[cur] == '\n')
		{
			buffer[cur] = 0;
			return true;
		}

		cur++;
		if (bufferSize <= cur)
		{
			buffer[cur] = 0;
			return true;
		}
	}
}

i32 CStreamingInstance::ReadInt32()
{
	i32 tmp;
	Read((u8*)&tmp, sizeof(i32));
	return tmp;
}

f32 CStreamingInstance::ReadFloat32()
{
	f32 tmp;
	Read((u8*)&tmp, sizeof(f32));
	return tmp;
}