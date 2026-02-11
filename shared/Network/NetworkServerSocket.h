#pragma once

class CNetworkServerSocket
{
private:
    i32 m_socket;

public:
	CNetworkServerSocket(); 
	virtual ~CNetworkServerSocket(); 
	
	bool OnCreate(u32 addrIP, u16 addrPort, i32 backlogCount = 65535);
	void OnDestroy();

	i32	AcceptConnection(struct timeval* timeout, struct sockaddr_in* pAddr = NULL, socklen_t* pSize = NULL); 
	i32	GetListenSocket();
};
