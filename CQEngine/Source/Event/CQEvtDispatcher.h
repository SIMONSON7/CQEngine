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

#include <vector>
#include <memory>
#include "CQMacros.h"

NS_CQ_BEGIN

class CQEvtListener;

class CQEvtDispatcher
{
public:
	virtual ~CQEvtDispatcher();

public:
	void onMousePressL(int _x, int _y);

	void onMousePressR(int _x, int _y);

	void onMouseReleaseL(int _x, int _y);

	void onMouseReleaseR(int _x, int _y);

	void onMouseWheel(int _x, int _y, int _zDelta);

public:
	void registerListener(std::shared_ptr<CQEvtListener> _listener);

	void unregisterListener(std::shared_ptr<CQEvtListener> _listener);

	void notify(unsigned int _evtID);

private:
	friend class CQCore;

	explicit CQEvtDispatcher();

	// non-copyable
	CQEvtDispatcher(const CQEvtDispatcher &) = delete;

	CQEvtDispatcher& operator=(const CQEvtDispatcher &) = delete;

private:
	std::vector<std::shared_ptr<CQEvtListener>> listenerVec_;

};

NS_CQ_END

#endif /* __CQEVTDISPATCHER_H__ */
