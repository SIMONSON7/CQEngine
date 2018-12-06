//*****************************************************************************
//
//! \file CQContext.h
//! \brief 
//! \author qiu_hao
//! \date 2018/12/06 11:19.pm
//
//*****************************************************************************
#ifndef __CQCONTEXT_H__
#define __CQCONTEXT_H__

#include "CQMacros.h"

NS_CQ_BEGIN

class CQContext
{
public:
	virtual ~CQContext();

public:
	virtual void initRenderContext() = 0;

	virtual void destroyRenderContext() = 0;

	virtual void swapFrameBuff() = 0;

	virtual void resizeView(int _width, int _height) = 0;
};

NS_CQ_END

#endif /* __CQCONTEXT_H__ */
