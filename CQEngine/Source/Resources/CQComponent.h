//*****************************************************************************
//
//! \file CQComponent.h
//! \brief 
//! \author qiu_hao
//! \date 2018/11/08 10:23.pm
//
//*****************************************************************************

#ifndef __CQCOMPONENT_H__
#define __CQCOMPONENT_H__

#include <string>
#include "CQMacros.h"

NS_CQ_BEGIN

class CQComponent
{
public:
	virtual const std::string& getName() const = 0;

};

NS_CQ_END

#endif /* __CQCOMPONENT_H__ */
