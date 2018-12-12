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
#include "CQInput.h"
#include "CQNoncopyable.h"

NS_CQ_BEGIN

class CQEvtListener;

class CQEvtDispatcher : private CQNoncopyable
{
public:
	virtual ~CQEvtDispatcher();

public:
	void registerListener(std::shared_ptr<CQEvtListener> _listener);

	void unregisterListener(std::shared_ptr<CQEvtListener> _listener);

	// The caller negative destructs _evt.
	void notify(CQInput::Evt* _evt);

private:
	friend class CQCore;

	explicit CQEvtDispatcher();

private:
	std::vector<std::shared_ptr<CQEvtListener>> listenerVec_;

};

NS_CQ_END

#endif /* __CQEVTDISPATCHER_H__ */
