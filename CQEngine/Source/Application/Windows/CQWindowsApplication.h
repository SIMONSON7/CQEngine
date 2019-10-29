//*****************************************************************************
//
//! \file CQWindowsApplication.h
//! \brief The application of Windows.
//! \author qiu_hao
//! \date 2019/10/29 11:09.pm
//
//*****************************************************************************
#ifndef __CQ_WINDOWSAPPLICATION_H__
#define __CQ_WINDOWSAPPLICATION_H__

#include "CQApplicationBase.h"

NS_CQ_BEGIN

class CQWindowsApplication : public CQApplicationBase
{
public:
	virtual ~CQWindowsApplication() {};
public:
	virtual void initialize();
	virtual void tick();
	virtual void finalize();

protected:

};

NS_CQ_END

#endif /*__CQ_WINDOWSAPPLICATION_H__*/



