#include "Network/NetworkServerSocket.h"
#include "Network/NetUtils.h"

CNetworkServerSocket::CNetworkServerSocket()
{
    //
}

CNetworkServerSocket::~CNetworkServerSocket()
{
    OnDestroy();
}

bool CNetworkServerSocket::OnCreate(u32 addrIP, u16 addrPort, i32 backlogCount)
{
	struct sockaddr_in sockAddr;

	SysMem::FillZero(&sockAddr, sizeof(sockAddr));
	sockAddr.sin_family			= AF_INET;
	sockAddr.sin_addr.s_addr	= addrIP;
	sockAddr.sin_port			= ::htons(addrPort);

	m_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	
	if (m_socket == INVALID_SOCKET) 
	{
        LOG_TRACE_FUNCTION("invalid socket.");
		return false;
	}

	i32 reuseOpt = 1;
    i32 reuseLen = sizeof(reuseOpt);

    // Sets a socket option
	::setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuseOpt, reuseLen);
 
	u64 argp = 1;

    // Controls the I/O mode of a socket
	::ioctl(m_socket, FIONBIO, &argp);

	if(::bind(m_socket, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR)
	{	
		LOG_TRACE_FUNCTION("bind failed.");
		return false;
	}

	if(::listen(m_socket, backlogCount ) == SOCKET_ERROR) 
	{
		LOG_TRACE_FUNCTION("listen failed.");
		return false;
	}

	return true; 
}

void CNetworkServerSocket::OnDestroy()
{
	if (m_socket != INVALID_SOCKET)
        ::close(m_socket);

	m_socket = INVALID_SOCKET;
}

i32	CNetworkServerSocket::AcceptConnection(struct timeval* timeout, struct sockaddr_in* pAddr, socklen_t* pSize)
{
	i32 socket_fd = INVALID_SOCKET;
	i32 listen_fd = m_socket;

	fd_set read_fds;
	FD_ZERO(&read_fds);
	FD_SET(listen_fd, &read_fds);

	i32 max_fd_plus_1 = listen_fd + 1;
	if (::select(max_fd_plus_1, &read_fds, NULL, NULL, timeout) == INVALID_SOCKET)
		return socket_fd;
    
	if (FD_ISSET(listen_fd, &read_fds))
	{
		socket_fd = ::accept(listen_fd, (struct sockaddr *)pAddr, pSize);
	}

	return socket_fd;
}

i32 CNetworkServerSocket::GetListenSocket()
{
    return m_socket;
}