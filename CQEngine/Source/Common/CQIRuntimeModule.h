//*****************************************************************************
//
//! \file CQIRuntimeModule.h
//! \brief The interface of engine module.
//! \author qiu_hao
//! \date 2019/10/26 11:39.pm
//
//*****************************************************************************
#ifndef __CQ_IRUNTIMEMODULE_H__
#define __CQ_IRUNTIMEMODULE_H__

#include "CQMacros.h"
#include "CQMemory.h"

NS_CQ_BEGIN

Interface CQIRuntimeModule
{
public:
	virtual ~CQIRuntimeModule() {};
public:
	virtual void initialize() = 0;
	virtual void tick()		  = 0;
	virtual void finalize()	  = 0;
};

NS_CQ_END

#endif /*__CQ_IRUNTIMEMODULE_H__*/



