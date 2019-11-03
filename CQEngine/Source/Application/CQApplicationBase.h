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

#include "CQIApplication.h"
#include "CQBaseRenderContext.h"

NS_CQ_BEGIN

class CQApplicationBase : implements CQIApplication
{
public:
	CQApplicationBase(const char * _appName, CQBaseRenderContext * _context);
	virtual ~CQApplicationBase() {};
public:
	virtual void initialize();
	virtual void tick();
	virtual void finalize();
	virtual bool isQuit();
protected:
	static bool isQuit_;
	const char * appName_;
	CQBaseRenderContext * renderContext_;

private:
	// enforce CQBaseRenderContext.
	CQApplicationBase() {}
};

NS_CQ_END

#endif /*__CQ_APPLICATIONBASE_H__*/



