//*****************************************************************************
//
//! \file CQNoncopyable.h
//! \brief Ensure classes derived from this class cannot be copied.
//! \author qiu_hao
//! \date 2018/12/12 10:58.pm
//
//*****************************************************************************
#ifndef __CQNONCOPYABLE__
#define __CQNONCOPYABLE__

#include "CQMacros.h"

NS_CQ_BEGIN

class CQNoncopyable
{
protected:
	CQNoncopyable() = default;
	~CQNoncopyable() = default;

	CQNoncopyable(const CQNoncopyable&) = delete;
	CQNoncopyable& operator=(const CQNoncopyable&) = delete;
};

NS_CQ_END

#endif /* __CQNONCOPYABLE__ */