#if defined(_MSC_VER)
	#define WIN32_LEAN_AND_MEAN
	#include<windows.h>
	#include<WinSock2.h>

	#pragma comment(lib,"ws2_32.lib")
#endif
#include <stdio.h>
#include "proto.h"

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

	do
	{
		sockaddr_in cAddr = {};
		int cAddrLen = sizeof(sockaddr_in);
		SOCKET cSock = INVALID_SOCKET;

		cSock = accept(sock, (sockaddr*)&cAddr, &cAddrLen);
		if (cSock == INVALID_SOCKET)
		{
			puts("SERVER ACCEPT CLIENT ERROR.");
		}
		printf("SERVER ACCEPT THE CLIENT FROM :%s\n", inet_ntoa(cAddr.sin_addr));

		Header head = {};
		recv(cSock, (char*)&head, sizeof(Header), 0);
		printf("client package size = %d.\n",head.len_);

		switch (head.code_)
		{
			case LOGIN :
			{
				LoginPackage login = {};
				recv(cSock, (char*)&login + sizeof(Header), head.len_ - sizeof(Header), 0);
				printf("client login name = %s,pwd = %s.\n",login.name_,login.pwd_);

				LoginRetPackage ret = {};
				strcpy(ret.result_, "token is right!");
				send(cSock, (char*)&ret, sizeof(ret), 0);
			}
				break;
			default:
				puts("ERROR : CLIENT DATA INVAILD.");
				break;
		}


		
	} while (true);

	closesocket(sock);
	WSACleanup();

	puts("Bay.");
	return 0;
}
#endif