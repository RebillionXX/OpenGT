#include "Network/NetUtils.h"

u32 NetUtil::StringToIPV4(std::string ipAddr)
{
    u32 convertIP;
    if (inet_pton(AF_INET, ipAddr.c_str(), &convertIP) <= 0)
        return 0;

    return convertIP;
}

u32 NetUtil::StringToIPV6(std::string ipAddr)
{
    u32 convertIP;
    if (inet_pton(AF_INET6, ipAddr.c_str(), &convertIP) <= 0)
        return 0;

    return convertIP;
}

char* NetUtil::IPV4ToString(u32 addrIP, char* szAddrIP)
{
	i32 count1 = 0;
	i32 count2;
	u32 tmp;
	char strTmp[4];

	for (i32 i = 0 ; i < 4 ; i++)
	{
		tmp = (addrIP >> (8 * i)) & 0x000000FF;

		count2 = 0;
		do
		{
			strTmp[count2] = (tmp % 10) + '0';
			tmp /= 10;
			count2++;
		} while (0 < tmp);
		
		do
		{
			count2--;
			szAddrIP[count1] = strTmp[count2];
			count1++;
		} while (0 < count2);
		szAddrIP[count1] = '.';
		count1++;
	}
	szAddrIP[count1 - 1] = '\0';

	return szAddrIP;
}