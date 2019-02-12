//*****************************************************************************
//
//! \file CQCamera.h
//! \brief 
//! \author qiu_hao
//! \date 2018/12/17 10:17.pm
//
//*****************************************************************************

#ifndef __CQCULLER_H__
#define __CQCULLER_H__

#include <vector>
#include "CQMacros.h"
#include "CQNoncopyable.h"

NS_CQ_BEGIN

class CQObject;

class CQCuller : CQNoncopyable
{
public:
	virtual ~CQCuller();

public:
	std::vector<CQObject*> getVisibleObjs();

private:
	friend class CQCore;

	explicit CQCuller();

private:
	bool __isVisible(CQObject * _obj);

private:
	std::vector<CQObject*> visibleObjs_;

};

NS_CQ_END

#endif /* __CQCULLER_H__ */