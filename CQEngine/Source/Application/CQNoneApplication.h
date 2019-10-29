//*****************************************************************************
//
//! \file CQNoneApplication.h
//! \brief Null object design pattern.
//! \author qiu_hao
//! \date 2019/10/29 11:22.pm
//
//*****************************************************************************
#ifndef __CQ_NONEAPPLICATION_H__
#define __CQ_NONEAPPLICATION_H__

#include "CQApplicationBase.h"

NS_CQ_BEGIN

class CQNoneApplication : public CQApplicationBase
{
public:
	virtual ~CQNoneApplication() {};
public:
	virtual void initialize() {};
	virtual void tick() {};
	virtual void finalize() {};
};

NS_CQ_END

#endif /*__CQ_NONEAPPLICATION_H__*/



