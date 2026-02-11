#pragma once

class CNodeSession
{
public:
    i32 m_nodeIdx;
    u32 m_connIP;
    char m_connStrIP[IP_ADDR_SIZE];

public:
    CNodeSession();
    virtual ~CNodeSession();
};