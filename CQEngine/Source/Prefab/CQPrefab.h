//*****************************************************************************
//
//! \file CQPrefab.h
//! \brief 
//! \author qiu_hao
//! \date 2019/04/03 11:03.pm
//
//*****************************************************************************
#ifndef __CQPREFAB_H__
#define __CQPREFAB_H__

#include "CQMacros.h"
#include <vector>

NS_CQ_BEGIN

Interface ICQPrefab
{
public:
	ICQPrefab() = default;

	virtual ~ICQPrefab() {};

public:
	virtual void setupGeometry() = 0;

	virtual void setupSurface() = 0;
};

NS_CQ_END

#endif /* __CQPREFAB_H__ */