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
	std::vector<CQObject*> getVisibleObjs();




};

NS_CQ_END

#endif /* __CQCULLER_H__ */