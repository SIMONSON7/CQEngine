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
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <arpa/inet.h>
	#include <string.h>

	#define SOCKET int
	#define INVALID_SOCKET  (SOCKET)(~0)
	#define SOCKET_ERROR            (-1)
#endif

#include "CQMacros.h"

NS_CQ_BEGIN

#if defined(_MSC_VER)
#	define CQSOCKET_START() \
	do { WORD ver = MAKEWORD(2, 2); WSADATA dat; WSAStartup(ver, &dat); } while(0)

#	define CQSOCKET_CLEAN() WSACleanup()
#else
#	define CQSOCKET_START()
#	define CQSOCKET_CLEAN()
#endif

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

	CQSocket(const PROTO_TYPE _pType, const IP_TYPE _ipType);

	virtual ~CQSocket();
public:
	/// idempotent ///
	bool Init();

	/// idempotent ///
	bool Init(const PROTO_TYPE _pType,const IP_TYPE _ipType);

	/// idempotent ///
	void Clean();

	/// Only for client.
	bool Connect(const std::string _ip,const short _port);

	/// Only for server.
	int Bind(const std::string _ip, const short _port);

	/// Only for server.
	int Listen(const int _backLog);

	/// Only for server.
	SOCKET Accept(sockaddr_in *_cAddr);

	///
	int Send(const char *_buf, const int _bufLen, int _sig , SOCKET _socket = INVALID_SOCKET);

	///
	int Recv(char *_buf, int _bufLen, int _sig , SOCKET _socket = INVALID_SOCKET);

	///
	bool IsReadAble();

	///
	bool IsWriteAble();

	///
	bool IsValid();

public:
	inline void setDesc(const std::string& _desc)
	{
		desc_ = _desc;
	}

	inline const std::string& getDesc() const
	{
		return desc_;
	}

	inline const SOCKET GetSocekt() const
	{
		return socket_;
	}
private:
	bool isIPV6_;

	std::string desc_;

	SOCKET socket_;
};

NS_CQ_END

#endif /*__CQSOCKET_H__*/
