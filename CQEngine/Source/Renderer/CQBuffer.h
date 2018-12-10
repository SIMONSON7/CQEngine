//*****************************************************************************
//
//! \file CQBuffer.h
//! \brief 
//! \author qiu_hao
//! \date 2018/12/04 10:35.pm
//
//*****************************************************************************
#ifndef __CQBUFFER_H__
#define __CQBUFFER_H__

#include "CQMacros.h"

NS_CQ_BEGIN

class CQBuffer
{
public:
	enum USAGE
	{
		STATIC,
		DYNAMIC,
		STREAM,
	};

public:
	virtual ~CQBuffer();

	CQBuffer(USAGE _usage);
	
public:
	USAGE getUsage() const;

	char* getData() const;

private:
	char* buffer_;
};

class CQVertexBuffer : public CQBuffer
{

};

class CQIndexBuffer : public CQBuffer
{

};

NS_CQ_END

#endif /* __CQBUFFER_H__ */

