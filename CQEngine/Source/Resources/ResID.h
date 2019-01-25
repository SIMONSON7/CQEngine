//*****************************************************************************
//
//! \file ResID.h
//! \brief 
//! \author qiu_hao
//! \date 2019/01/25 03:52.pm
//
//*****************************************************************************
#ifndef __RESID_H__
#define __RESID_H__

#include "CQMacros.h"
#include "CQNoncopyable.h"

NS_CQ_BEGIN

class ResID : private CQNoncopyable
{
public:
	static const unsigned int INVALID = 0xFFFFFFFF;

public:
	ResID() { value_ = INVALID; }

	ResID(unsigned int _value) { value_ = _value; }

	~ResID() {}
	
public:
	bool operator== (const ResID & _res) const { return value_ == _res.value_; }

	bool operator!= (const ResID & _res) const { return value_ != _res.value_; } 

private:
	unsigned int value_;

};

NS_CQ_END

#endif /* __RESID_H__ */

