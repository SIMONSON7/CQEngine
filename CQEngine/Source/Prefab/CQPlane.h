//*****************************************************************************
//
//! \file CQPlane.h
//! \brief 
//! \author qiu_hao
//! \date 2019/04/04 11:33.pm
//
//*****************************************************************************
#ifndef __CQPLANE_H__
#define __CQPLANE_H__

#include "CQMacros.h"
#include "CQPrefab.h"

NS_CQ_BEGIN

class CQPlane : public CQPrefab
{
public:
	CQPlane();

	virtual ~CQPlane();

public:
	virtual void setupGeometry();

	virtual void setupSurface();
};

NS_CQ_END

#endif /* __CQPLANE_H__ */