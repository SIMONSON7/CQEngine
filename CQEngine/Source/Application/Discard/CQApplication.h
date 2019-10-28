//*****************************************************************************
//
//! \file CQApplication.h
//! \brief 
//! \author qiu_hao
//! \date 2018/02/05 18:21.pm
//
//*****************************************************************************
#ifndef __CQAPPLICATION_H__
#define __CQAPPLICATION_H__

#include "CQMacros.h"
#include "CQMemory.h"

NS_CQ_BEGIN

Interface CQAppI
{
public:
	virtual ~CQAppI() = 0;

public:
	virtual void run()      = 0;
	virtual void init()		= 0;
	virtual void tick()		= 0;
	virtual void destroy()	= 0;

};

NS_CQ_END

#include "CQApplication.inl"

//extern NS_CQ::CQAppI *g_pApp;

#endif /*__CQAPPLICATION_H__*/



