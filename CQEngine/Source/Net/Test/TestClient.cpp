#if defined(_MSC_VER)
	#define WIN32_LEAN_AND_MEAN
	#include<windows.h>
	#include<WinSock2.h>

	#pragma comment(lib,"ws2_32.lib")
#endif
#include <stdio.h>
#include "proto.h"

#if 1
int main(int argc,char *argv[])
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
	int ret = connect(sock, (sockaddr*)&sin, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR)
	{
		printf("CONNECT SOCKET FAIL, RET_CODE = %d.\n",ret);
		return -1;
	}
	puts("CONNECT SERVER SUCCESS.");

	char cmdBuf[512] = {};
	char recvBuf[512] = {};
	do
	{
		scanf("%s",cmdBuf);
		if ((!strcmp(cmdBuf,"exit")) 
			|| (!strcmp(cmdBuf,"EXIT")))
		{
			break;
		}

		send(sock, cmdBuf, sizeof(cmdBuf), 0);

		size_t len = recv(sock, recvBuf, sizeof(recvBuf), 0);
		if (len > 0)
		{
			printf("RECV FROM SERVER :%s",recvBuf);
		}

	} while (true);

	closesocket(sock);
	WSACleanup();
	
	puts("Bay.");
	return 0;
}
#endif