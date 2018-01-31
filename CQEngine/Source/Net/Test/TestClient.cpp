#include "CQMacros.h"

#if defined(_MSC_VER)
#define WIN32_LEAN_AND_MEAN
#include<windows.h>
#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib")
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define SOCKET int
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)
#endif

#if defined CQ_USE_CPP11
#include <thread>
#endif
#include <stdio.h>
#include "proto.h"
#include "CQSocket.h"

USING_NS_CQ

bool g_bExit = false;
void inputWork(CQSocket *_socket)
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
			_socket->Send((const char *)&login, login.head_.len_);
		}

	} while (!g_bExit);
}

int cWork(CQSocket *_socket)
{
	Header head = {};
	int len = _socket->Recv((char *)&head, sizeof(Header));
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
			char buf[64];
			int len = _socket->Recv(buf, 64);
			if (len > 0)
			{
				printf("recv from server :%s\n", buf);
			}
		}
		break;
		default:
		{
			puts("ERROR : server data invalid.");
			return -1;
		}
	}

	return 1;
}

#if 1
int main(int argc, char *argv[])
{
	CQSOCKET_START();

	CQSocket socket;
	socket.Connect("127.0.0.1", 4567);
	
	std::thread td(inputWork, &socket);
	td.detach();
	do
	{
		// client loop begine //
		if (socket.IsReadAble())
		{
			int ret = cWork(&socket);
			if (ret <= 0)
			{
				puts("client exit.");
				break;
			}
		}
		if (socket.IsWriteAble())
		{
			//puts("client socket is writeable.");
		}
		// client loop end //

	} while (!g_bExit);

	// clean
	CQSOCKET_CLEAN();

	puts("Bay.");
	return 0;
}
#endif