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

void CQSocket::Init(PROTO_TYPE _pType, IP_TYPE _ipType)
{
	if (IsValid()) return;
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
		puts("CREATE SOCKET FAIL.");
		return;
	}
	puts("INIT SOCKET SUCCESS.");
}

void CQSocket::Init()
{
	if (IsValid()) return;
#if defined(_MSC_VER)
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
#endif

	socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket_ == INVALID_SOCKET)
	{
		puts("CREATE SOCKET FAIL.");
		return ;
	}
	puts("INIT SOCKET SUCCESS.");
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
		printf("CONNECT SOCKET FAIL, RET_CODE = %d.\n", ret);
		return false;
	}

	puts("CONNECT SERVER SUCCESS.");
	return true;
}

bool CQSocket::IsValid()
{
	return socket_ == INVALID_SOCKET ? false : true;
}