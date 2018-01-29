#include "CQSocket.h"

USING_NS_CQ

CQSocket::CQSocket() 
{
	Init();
}

CQSocket::~CQSocket() 
{
	if (!IsValid()) return;
	Clean();
}

void CQSocket::Init()
{
	if (IsValid()) return;
#if defined(_MSC_VER)
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
#endif
}

void CQSocket::Clean()
{
#if defined(_MSC_VER)
	closesocket(socket_);
	WSACleanup();
#else
	close(socket_);
#endif

	socket_ = INVALID_SOCKET;
}

bool CQSocket::IsValid()
{
	return socket_ == INVALID_SOCKET ? false : true;
}