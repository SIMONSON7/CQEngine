//*****************************************************************************
//
//! \file CQEvtDispatcher.h
//! \brief A tiny event dispatcher.
//! \author qiu_hao
//! \date 2018/11/23 05:15.pm
//
//*****************************************************************************
#ifndef __CQEVTDISPATCHER_H__
#define __CQEVTDISPATCHER_H__

#include "CQMacros.h"

NS_CQ_BEGIN

class CQEvtDispatcher
{
public:
	virtual ~CQEvtDispatcher();

public:
	void onMousePressL();

	void onMouseReleaseR();

private:
	friend class CQCore;

	explicit CQEvtDispatcher();

	// non-copyable
	CQEvtDispatcher(const CQEvtDispatcher &) = delete;

	CQEvtDispatcher& operator=(const CQEvtDispatcher &) = delete;

};

NS_CQ_END

#endif /* __CQEVTDISPATCHER_H__ */
