#include "CQMacros.h"

#if defined CQ_USE_CPP11
#include <thread>
#endif
#include <stdio.h>
#include "proto.h"
#include "CQSocket.h"

USING_NS_CQ

#define _STICKPKG_TEST_ 1

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
			_socket->Send((const char *)&login, login.head_.len_,0);
		}

	} while (!g_bExit);
}

int cWork(CQSocket *_socket)
{
	Header head = {};
	int len = _socket->Recv((char *)&head, sizeof(Header),0);
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
			int len = _socket->Recv(buf, 64,0,_socket->GetSocekt());
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

#if 0
int main(int argc, char *argv[])
{
	CQSOCKET_START();

	CQSocket socket;
	socket.Connect("127.0.0.1", 4567);
	
	std::thread td(inputWork, &socket);
	td.detach();
	do
	{
#if _STICKPKG_TEST_
		StickPackageTest sp = {};
		strcpy(sp.data_, "This is a long long long long long long long long long long long long text for test.");
		socket.Send((const char *)&sp, sp.head_.len_, 0);
#endif
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