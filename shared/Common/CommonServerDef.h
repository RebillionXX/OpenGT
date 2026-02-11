#pragma once

// Application Server Communication

enum ASC_SERVER_TYPE
{
    ASC_SERVER_NONE         = -1,
    ASC_SERVER_LOGON        = 0,
    ASC_SERVER_TRANS        = 1,
    ASC_SERVER_GAME         = 2,
    ASC_SERVER_MESSENGER    = 3,
    ASC_SERVER_UPDATER      = 4, // Currently un-used, planning to use as in-game event updater e.g. Guild Event
	ASC_SERVER_COUNT,
};

struct SERVER_INFO_COMMON
{
    u32 m_connIP;
    u16 m_connPort;
    u8 m_type;
};