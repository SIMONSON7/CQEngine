//*****************************************************************************
//
//! \file CQBaseRenderContext.h
//! \brief The base class of render context.
//! \author qiu_hao
//! \date 2019/11/02 11:14.pm
//
//*****************************************************************************
#ifndef __CQBASERENDERCONTEXT_H__
#define __CQBASERENDERCONTEXT_H__

#include "CQIRenderContext.h"

NS_CQ_BEGIN

class CQBaseRenderContext : implements CQIRenderContext
{
public:
	CQBaseRenderContext(CQFrameConfiguration & config) { config_ = config; }
	virtual ~CQBaseRenderContext() {};
public:
	virtual void initContext() {};
	virtual void destroyContext() {};
	virtual void swapFrameBuff() {};
public:
	const CQFrameConfiguration getFrameConfiguration() const { return config_; }
protected:
	CQFrameConfiguration config_;
};

NS_CQ_END

#endif /*__CQBASERENDERCONTEXT_H__*/
