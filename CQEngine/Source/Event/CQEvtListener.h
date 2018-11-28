//*****************************************************************************
//
//! \file CQEvtListener.h
//! \brief A tiny event listener.
//! \author qiu_hao
//! \date 2018/11/23 05:16.pm
//
//*****************************************************************************
#ifndef __CQEVTLISTENER_H__
#define __CQEVTLISTENER_H__

#include "CQMacros.h"
#include "CQAction.h"

NS_CQ_BEGIN

// TODO:
// Very similar to TimeAction, except that one is based on time and one is based on events. 
// Both can be unified in the future.

class CQEvtListener
{
public:
	explicit CQEvtListener();

	CQEvtListener(unsigned int _evtID, Action *_cb);

	virtual ~CQEvtListener();

public:
	void setEvtID(unsigned int _evtID);
	
	void setCB(Action *_cb);

	unsigned int getEvtID() const;

	Action *getCB();

	bool isCBValid();

private:
	// non-copyable
	CQEvtListener(const CQEvtListener &) = delete;

	CQEvtListener& operator=(const CQEvtListener &) = delete;

private:
	unsigned int evtID_;

	Action *cb_;
};

NS_CQ_END

#endif /* __CQEVTLISTENER_H__ */

