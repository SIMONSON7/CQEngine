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

NS_CQ_BEGIN

class CQEvtListener
{
public:
	explicit CQEvtListener();

	virtual ~CQEvtListener();

public:

private:
	// non-copyable
	CQEvtListener(const CQEvtListener &) = delete;

	CQEvtListener& operator=(const CQEvtListener &) = delete;

};

NS_CQ_END

#endif /* __CQEVTLISTENER_H__ */

