#pragma once
#include <arpa/inet.h>
#include <sys/ioctl.h>

namespace NetUtil
{
    u32 StringToIPV4(std::string ipAddr);
    u32 StringToIPV6(std::string ipAddr);

    char* IPV4ToString(u32 addrIP, char* szAddrIP);
}