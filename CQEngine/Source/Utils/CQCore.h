//*****************************************************************************
//
//! \file CQCore.h
//! \brief Core system management.
//! \author qiu_hao
//! \date 2018/08/19	09:35.pm
//
//*****************************************************************************
#ifndef __CQCORE_H__
#define __CQCORE_H__

#include "CQMacros.h"
#include "CQNoncopyable.h"

NS_CQ_BEGIN

class CQTime;
class CQScheduler;
class CQEvtDispatcher;
class CQResManager;
class CQRenderer;

class CQCore : private CQNoncopyable
{
public:
	static
	CQCore *shareCore();

	virtual ~CQCore();

public:
	CQTime *shareCQTime();

	CQScheduler *shareCQScheduler();

	CQEvtDispatcher *shareEvtDispatcher();

	CQResManager *shareResManager();

	CQRenderer *shareCQRender();

public:
	void updateTime();

	void updateScheduler();

private:
	explicit CQCore();

private:
	CQTime *time_;

	CQScheduler *scheduler_;

	CQEvtDispatcher *evtDispatcher_;

	CQResManager *resManager_;

	CQRenderer *render_;

};

NS_CQ_END

#endif /* __CQCORE_H__ */