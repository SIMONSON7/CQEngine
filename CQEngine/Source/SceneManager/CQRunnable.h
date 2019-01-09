//*****************************************************************************
//
//! \file CQRunnable.h
//! \brief 
//! \author qiu_hao
//! \date 2019/01/07 11:15.pm
//
//*****************************************************************************
#ifndef __CQRUNNABLE_H__
#define __CQRUNNABLE_H__

#include "CQMacros.h"

NS_CQ_BEGIN

class CQRunnable
{
public:
	virtual void onInit() = 0;

	virtual void update() = 0;

	virtual void onDestory() = 0;
};

NS_CQ_END

#endif /* __CQRUNNABLE_H__ */