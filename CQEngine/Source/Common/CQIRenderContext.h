//*****************************************************************************
//
//! \file CQIRenderContext.h
//! \brief The interface of render context.
//! \author qiu_hao
//! \date 2019/10/31 11:47.pm
//
//*****************************************************************************
#ifndef __CQ_IRENDERCONTEXT_H__
#define __CQ_IRENDERCONTEXT_H__

#include "CQFrameConfiguration.h"

NS_CQ_BEGIN

Interface CQIRenderContext
{
public:
	CQIRenderContext(CQFrameConfiguration & config) {}
	virtual ~CQIRenderContext() {};
public:
	virtual void initContext()    = 0;
	virtual void destroyContext() = 0;
	virtual void swapFrameBuff()  = 0;
	//virtual void resize()		  = 0;
};

NS_CQ_END

#endif /*__CQ_IRENDERCONTEXT_H__*/



