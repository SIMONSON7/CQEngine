//*****************************************************************************
//
//! \file CQResI.h
//! \brief 
//! \author qiu_hao
//! \date 2019/01/25 05:09.pm
//
//*****************************************************************************
#ifndef __CQRESI_H__
#define __CQRESI_H__

#include "CQMacros.h"
#include "ResID.h"

NS_CQ_BEGIN

class CQResI
{
public:
	virtual ResID getResID() const = 0;
	virtual void onResInit() = 0;
	virtual void onResDestory() = 0;
};


NS_CQ_END

#endif /* __CQRESI_H__ */
