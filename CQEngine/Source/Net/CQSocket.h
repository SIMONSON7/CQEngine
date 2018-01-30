/*
*
*		qiu_hao		2018/01/28		10:55.pm
*/
#ifndef __CQSOCKET_H__
#define __CQSOCKET_H__

#include <string>

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

#include "CQMacros.h"

NS_CQ_BEGIN

class CQSocket
{
public:
	enum PROTO_TYPE 
	{
		TCP,
		UDP
	};

	enum IP_TYPE
	{
		IPV4,
		IPV6
	};

public:
	CQSocket();

	CQSocket(PROTO_TYPE _pType, IP_TYPE _ipType);

	virtual ~CQSocket();
public:
	/// idempotent ///
	void Init();

	/// idempotent ///
	void Init(PROTO_TYPE _pType,IP_TYPE _ipType);

	/// idempotent ///
	void Clean();

	///
	bool Connect(const std::string _ip,const short _port);

	///
	int Send(const char *_buf, const int _bufLen, int _sig = 0);

	///
	int Recv(char *_buf, int _bufLen, int _sig = 0);

	///
	bool IsReadAble();

	///
	bool IsWriteAble();

	///
	void Listen();

	///
	void Bind();

	///
	bool IsValid();

private:

	SOCKET socket_;
};

NS_CQ_END

#endif /*__CQSOCKET_H__*/