#include "CQMacros.h"

#if defined(_MSC_VER)
	#define WIN32_LEAN_AND_MEAN
	#include<windows.h>
	#include<WinSock2.h>

	#pragma comment(lib,"ws2_32.lib")
#else
	#include <unistd.h>
	#include <arpa/inet.h>
	#include <string>

	#define SOCKET int
	#define INVALID_SOCKET  (SOCKET)(~0)
	#define SOCKET_ERROR            (-1)
#endif

#if defined CQ_USE_CPP11
	#include <thread>
#endif
#include <stdio.h>
#include "proto.h"

bool g_bExit = false;
void inputWork(SOCKET _sock)
{
	do
	{
		char cmdBuf[512] = {};
		scanf("%s", cmdBuf);
		if ((!strcmp(cmdBuf, "exit"))
			|| (!strcmp(cmdBuf, "EXIT")))
		{
			g_bExit = true;
		}

		if (!strcmp(cmdBuf, "login"))
		{
			LoginPackage login = {};
			strcpy(login.name_, "simon");
			strcpy(login.pwd_, "pwd");
			send(_sock, (char*)&login, sizeof(LoginPackage), 0);
		}

	} while (!g_bExit);
}

int cWork(SOCKET _sock)
{
	Header head = {};
	int len = recv(_sock, (char*)&head, sizeof(Header), 0);
	if (len > 0)
	{
		printf("server package size = %d.\n", head.len_);
	}
	else if (len == 0)
	{
		puts("server exit.");
		return 0;
	}
	else
	{
		puts("recv msg exception.");
		return -1;
	}

	// recv from server
	switch (head.code_)
	{
	case LOGIN_RET:
	{
		LoginRetPackage loginRet = {};
		int len = recv(_sock, (char*)&loginRet, sizeof(LoginPackage), 0);
		if (len > 0)
		{
			printf("RECV FROM SERVER :%s", loginRet.result_);
		}
	}
		return 1;
	default:
		puts("ERROR : SERVER DATA INVAILD.");
		return 0;
	}

	return 1;
}

#if 1
int main(int argc,char *argv[])
{
#if defined(_MSC_VER)
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
#endif
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
#if defined(_MSC_VER)
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
#else
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
#endif
	int ret = connect(sock, (sockaddr*)&sin, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR)
	{
		printf("CONNECT SOCKET FAIL, RET_CODE = %d.\n",ret);
		return -1;
	}
	puts("CONNECT SERVER SUCCESS.");

	std::thread td(inputWork,sock);
	td.detach();
	do
	{
		// init fd_set
		fd_set r_fd_set;
		fd_set w_fd_set;
		fd_set exp_fd_set;

		FD_ZERO(&r_fd_set);
		FD_ZERO(&w_fd_set);
		FD_ZERO(&exp_fd_set);

		// set fd_Set
		FD_SET(sock, &r_fd_set);
		FD_SET(sock, &w_fd_set);
		FD_SET(sock, &exp_fd_set);

		// select
		// select
		timeval tv = { 0,0 };
		int ret = select(sock + 1, &r_fd_set, &w_fd_set, &exp_fd_set, &tv);
		if (ret < 0)
		{
			puts("CLIENT SELECT ERROR.");
			break;
		}

		// handle client sock : new message
		if (FD_ISSET(sock, &r_fd_set))
		{
			FD_CLR(sock, &r_fd_set);

			int ret = cWork(sock);
			if (ret <= 0)
			{
				puts("CLIENT EXIT");
				break;
			}
		}
	} while (!g_bExit);

	// clean
#if defined(_MSC_VER)
	closesocket(sock);
	WSACleanup();
#else
	close(sock);
#endif
	
	puts("Bay.");
	return 0;
}
#endif