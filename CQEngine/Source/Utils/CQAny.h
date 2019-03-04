//*****************************************************************************
//
//! \file CQAny.h
//! \brief An implementation of std::any (C++17).
//! \author qiu_hao
//! \date 2019/03/04 05:51.pm
//
//*****************************************************************************
#ifndef __CQANY_H__
#define __CQANY_H__

#include "CQMacros.h"
#include "CQMemory.h"

NS_CQ_BEGIN;

template<typename T>
class CQAny
{
public:
	CQAny(T * _content)
		:
		content_(_content)
	{}
	
	CQAny & operator=(T * _content)
	{
		__set(_content);
		return *this;
	}

	~CQAny()
	{
		CQ_DELETE(content_, T);
	}

public:
	T & getRealContent()
	{
		CQASSERT(content_);
		return *reinterpret_cast<T*>(content_);
	}
	
	const T & getRealContent() const
	{
		CQASSERT(content_);
		return *reinterpret_cast<T*>(content_);
	}

private:
	void __set(T * _realContent)
	{
		content_ = reinterpret_cast<void*>(_realContent);
	}

private:
	void * content_;
};

NS_CQ_END;

#endif /* __CQANY_H__ */
