#include "CQSocket.h"

USING_NS_CQ

CQSocket::CQSocket() 
{
	Init();
}

CQSocket::CQSocket(PROTO_TYPE _pType, IP_TYPE _ipType)
{
	Init(_pType,_ipType);
}

CQSocket::~CQSocket() 
{
	Clean();
}

void CQSocket::Init()
{
	Init(CQEngine::CQSocket::TCP, CQEngine::CQSocket::IPV4);
}

void CQSocket::Init(PROTO_TYPE _pType, IP_TYPE _ipType)
{
	if (!IsValid()) return;
#if defined(_MSC_VER)
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
#endif

	socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_pType == CQEngine::CQSocket::UDP)
	{
		//socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_UDP);
	}
	if (_ipType == CQEngine::CQSocket::IPV6)
	{
		//socket_ = socket(AF_INET6, SOCK_STREAM, IPPROTO_UDP);
	}

	if (socket_ == INVALID_SOCKET)
	{
		puts("[CQSOCKET] CREATE SOCKET FAIL.");
		return;
	}
	puts("[CQSOCKET] INIT SOCKET SUCCESS.");
}

void CQSocket::Clean()
{
	if (!IsValid()) return;
#if defined(_MSC_VER)
	closesocket(socket_);
	WSACleanup();
#else
	close(socket_);
#endif

	socket_ = INVALID_SOCKET;
}

bool CQSocket::Connect(const std::string _ip, const short _port)
{
	if (!IsValid())
	{
		return false;
	}

	sockaddr_in sin = {};
	sin.sin_family = AF_INET;
	sin.sin_port = htons(_port);
#if defined(_MSC_VER)
	sin.sin_addr.S_un.S_addr = inet_addr(_ip.c_str());
#else
	sin.sin_addr.s_addr = inet_addr(_ip.c_str());
#endif
	int ret = connect(socket_, (sockaddr*)&sin, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR)
	{
		printf("[CQSOCKET] CONNECT SOCKET FAIL, RET_CODE = %d.\n", ret);
		return false;
	}

	puts("[CQSOCKET] CONNECT SERVER SUCCESS.");
	return true;
}

int CQSocket::Send(const char *_buf,const int _bufLen,int _sig /*= 0*/)
{
	int ret = send(socket_, _buf, _bufLen, _sig);
	return ret;
}

int CQSocket::Recv(char *_buf, int _bufLen, int _sig /*= 0*/)
{
	int ret = recv(socket_, _buf, _bufLen, _sig);
	return ret;
}

bool CQSocket::IsReadAble()
{
	if (!IsValid())
	{
		return false;
	}

	fd_set r_fd_set;
	FD_ZERO(&r_fd_set);
	FD_SET(socket_, &r_fd_set);

	// select
	timeval tv = { 0,0 };
	int ret = select(socket_ + 1, &r_fd_set, 0, 0, &tv);
	
	if (ret > 0)
	{
		if (FD_ISSET(socket_, &r_fd_set))
		{
			FD_CLR(socket_, &r_fd_set);
			return true;
		}
	}
	// ret == 0 : select time out
	// ret == -1
	if (ret == -1)
	{
		puts("[CQSocket] SELECT READ_SET OCCUR ERROR.");
	}
	return false;
}

bool CQSocket::IsWriteAble()
{
	if (!IsValid())
	{
		return false;
	}

	fd_set w_fd_set;
	FD_ZERO(&w_fd_set);
	FD_SET(socket_, &w_fd_set);

	// select
	timeval tv = { 0,0 };
	int ret = select(socket_ + 1, 0, &w_fd_set, 0, &tv);
	if (ret >= 0)
	{
		if (FD_ISSET(socket_, &w_fd_set))
		{
			FD_CLR(socket_, &w_fd_set);
			return true;
		}
	}
	else
	{
		//puts("[CQSOCKET] CLIENT SELECT ISWRITEDABEL ERROR.");
		return false;
	}
	return true;
}

bool CQSocket::IsValid()
{
	return socket_ == INVALID_SOCKET ? false : true;
}