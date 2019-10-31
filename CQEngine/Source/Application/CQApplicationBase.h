//*****************************************************************************
//
//! \file CQApplicationBase.h
//! \brief The base class of application.
//! \author qiu_hao
//! \date 2019/10/27 08:55.pm
//
//*****************************************************************************
#ifndef __CQ_APPLICATIONBASE_H__
#define __CQ_APPLICATIONBASE_H__

#include "CQIRenderContext.h"
#include "CQIApplication.h"

NS_CQ_BEGIN

class CQApplicationBase : implements CQIApplication
{
public:
	CQApplicationBase(CQIRenderContext * _context);
	virtual ~CQApplicationBase() {};
public:
	virtual void initialize();
	virtual void tick();
	virtual void finalize();
	virtual bool isQuit();
protected:
	bool isQuit_;
	CQIRenderContext * renderContext_;
};

NS_CQ_END

#endif /*__CQ_APPLICATIONBASE_H__*/



