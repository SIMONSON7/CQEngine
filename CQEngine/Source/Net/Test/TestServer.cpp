#include "CQMacros.h"

#if defined CQ_USE_CPP11
#include <thread>
#endif
#include <stdio.h>
#include <vector>
#include "proto.h"
#include "CQSocket.h"
#include "CQDebug.h"

USING_NS_CQ

int work(SOCKET _cSock)
{
	Header head = {};
	int len = recv(_cSock, (char*)&head, sizeof(Header), 0);
	if (len > 0)
	{
		printf("client package size = %d.\n", head.len_);
	}
	else if (len == 0)
	{
		puts("client exit.");
		return 0;
	}
	else
	{
		puts("recv msg exception.");
		return -1;
	}

	switch (head.code_)
	{
	case LOGIN:
	{
		LoginPackage login = {};
		int ret = recv(_cSock, (char*)&login + sizeof(Header), head.len_ - sizeof(Header), 0);
		if (len > 0)
		{
			printf("client login name = %s,pwd = %s.\n", login.name_, login.pwd_);
		}

		LoginRetPackage retPak = {};
		strcpy(retPak.result_, "token is right!");
		send(_cSock, (char*)&retPak, sizeof(retPak), 0);
	}
		return 1;
	case STICKPKG_TEST:
	{
		StickPackageTest sp = {};
		int ret = recv(_cSock, (char*)&sp + sizeof(Header), head.len_ - sizeof(Header), 0);
		if (len > 0)
		{
			printf("client stickPackage data = %s\n.", sp.data_);
		}
	}
		return 1;
	default:
		puts("ERROR : CLIENT DATA INVAILD.");
		return 0;
	}

	return 1;
}

#if 1
int main(int argc, char *argv[])
{
	CQSOCKET_START();

	CQSocket s_sock(CQSocket::TCP,CQSocket::IPV4);

	// bind //
	int ret = s_sock.Bind("127.0.0.1",4567);
	if (ret == SOCKET_ERROR)
	{
		printf("server bind socket error :%d\n", getSocketError());
		return -1;
	}
	puts("server bind success.");

	ret = s_sock.Listen(100);
	if (ret == SOCKET_ERROR)
	{
		printf("server listen socket error :%d\n", getSocketError());
		return -1;
	}
	puts("server listen success.");
	puts("===== SERVER INIT SUCCESS ======");

	std::vector<SOCKET> c_socks;
	do
	{
		// init fd_set
		fd_set r_fd_set;
		FD_ZERO(&r_fd_set);
		FD_SET(s_sock.GetSocekt(), &r_fd_set);

		SOCKET max_sock = s_sock.GetSocekt();
		for (int i = 0 ; i < c_socks.size();++i)
		{
			FD_SET(c_socks[i], &r_fd_set);
			max_sock = max_sock < c_socks[i] ? c_socks[i] : max_sock;
		}

		// select
		timeval tv = {0,0};
		int ret = select(max_sock + 1,&r_fd_set,0,0,&tv);
		if (ret < 0)
		{
			puts("SERVER SELECT ERROR.");
			break;
		}
		// handle server sock : new client accept
		if (FD_ISSET(s_sock.GetSocekt(), &r_fd_set))
		{
			FD_CLR(s_sock.GetSocekt(), &r_fd_set);

			sockaddr_in cAddr = {};
			SOCKET sock = s_sock.Accept(&cAddr);
			if (sock == INVALID_SOCKET)
			{
				puts("SERVER ACCEPT CLIENT ERROR.");
			}
			else
			{
				c_socks.push_back(sock);
				printf("SERVER ACCEPT NEW CLIENT FROM :%s\n", inet_ntoa(cAddr.sin_addr));
			}
		}

		// handle clients sock : recv message
		for (int i = 0; i < c_socks.size(); ++i)
		{
			if (FD_ISSET(c_socks[i], &r_fd_set))
			{
				int ret = work(c_socks[i]);
				if (ret <= 0)
				{
#if defined(_MSC_VER)
					closesocket(c_socks[i]);
#else
					close(c_socks[i]);
#endif
					c_socks.erase(c_socks.begin() + i);
					puts("close client socket.");
				}
			}
		}
		
	} while (true);

	// clean
	CQSOCKET_CLEAN();
#if defined(_MSC_VER)
	for (int i = 0; i < c_socks.size(); ++i)
	{
		closesocket(c_socks[i]);
	}
#else
	for (int i = 0; i < c_socks.size(); ++i)
	{
		close(c_socks[i]);
	}
#endif
	puts("Bay.");
	return 0;
}
#endif 