#if defined(_MSC_VER)
	#define WIN32_LEAN_AND_MEAN
	#include<windows.h>
	#include<WinSock2.h>

	#pragma comment(lib,"ws2_32.lib")
#endif
#include <stdio.h>
#include <vector>
#include "proto.h"

void work(SOCKET _cSock)
{
	Header head = {};
	recv(_cSock, (char*)&head, sizeof(Header), 0);
	printf("client package size = %d.\n", head.len_);

	switch (head.code_)
	{
	case LOGIN:
	{
		LoginPackage login = {};
		recv(_cSock, (char*)&login + sizeof(Header), head.len_ - sizeof(Header), 0);
		printf("client login name = %s,pwd = %s.\n", login.name_, login.pwd_);

		LoginRetPackage ret = {};
		strcpy(ret.result_, "token is right!");
		send(_cSock, (char*)&ret, sizeof(ret), 0);
	}
		return;
	default:
		puts("ERROR : CLIENT DATA INVAILD.");
		return;
	}
}

#if 1
int main(int argc, char *argv[])
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		puts("CREATE SOCKET FAIL.");
		return -1;
	}
	puts("INIT SOCKET SUCCESS.");

	sockaddr_in sin = {};
	sin.sin_family = AF_INET;
	sin.sin_port = htons(4567);
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int ret = bind(sock, (sockaddr*)&sin, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR)
	{
		printf("BIND SOCKET FAIL, RET_CODE = %d.\n", ret);
		return -1;
	}
	puts("SERVER BIND SUCCESS.");

	ret = listen(sock, 100);
	if (ret == SOCKET_ERROR)
	{
		printf("LISTEN SOCKET FAIL, RET_CODE = %d.\n", ret);
		return -1;
	}
	puts("SERVER LISTEN SUCCESS.");
	puts("===== SERVER INIT SUCCESS ======");

	std::vector<SOCKET> c_socks;
	do
	{
		// SELECT //
		fd_set read_fd;
		fd_set write_fd;
		fd_set exp_fd;

		FD_ZERO(&read_fd);
		FD_ZERO(&write_fd);
		FD_ZERO(&exp_fd);

		FD_SET(sock, &read_fd);
		FD_SET(sock, &write_fd);
		FD_SET(sock, &exp_fd);

		for (int i = 0 ; i < c_socks.size();++i)
		{
			FD_SET(c_socks[i], &read_fd);
		}

		int ret = select(sock + 1,&read_fd,&write_fd,&exp_fd,nullptr);
		if (ret < 0)
		{
			puts("SERVER SELECT ERROR.");
			break;
		}
		if (FD_ISSET(sock, &read_fd))
		{
			FD_CLR(sock, &read_fd);

			sockaddr_in cAddr = {};
			int cAddrLen = sizeof(sockaddr_in);
			SOCKET cSock = INVALID_SOCKET;

			cSock = accept(sock, (sockaddr*)&cAddr, &cAddrLen);
			if (cSock == INVALID_SOCKET)
			{
				puts("SERVER ACCEPT CLIENT ERROR.");
			}
			c_socks.push_back(cSock);
			printf("SERVER ACCEPT THE CLIENT FROM :%s\n", inet_ntoa(cAddr.sin_addr));
		}

		for (int i = 0; i < read_fd.fd_count; ++i)
		{
			work(read_fd.fd_array[i]);
		}
		
	} while (true);

	closesocket(sock);
	WSACleanup();

	puts("Bay.");
	return 0;
}
#endif 