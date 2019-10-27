//*****************************************************************************
//
//! \file CQIApplication.h
//! \brief The interface of application.
//! \author qiu_hao
//! \date 2019/10/27 08:55.pm
//
//*****************************************************************************
#ifndef __CQ_IAPPLICATION_H__
#define __CQ_IAPPLICATION_H__

#include "CQIRuntimeModule.h"

NS_CQ_BEGIN

Interface CQIApplication : implements CQIRuntimeModule
{
public:
	virtual ~CQIApplication() {};
public:
	// IRuntimeModule interface.
	virtual void initialize() = 0;
	virtual void tick()		  = 0;
	virtual void finalize()	  = 0;

	// relative native code.
	virtual bool isQuit()     = 0;
};

NS_CQ_END

// declare global pointer of application.
extern NS_CQ::CQIApplication * g_pApplication;

#endif /*__CQ_IAPPLICATION_H__*/
