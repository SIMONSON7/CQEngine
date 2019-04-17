//*****************************************************************************
//
//! \file CQCube.h
//! \brief 
//! \author qiu_hao
//! \date 2019/04/17 04:05.pm
//
//*****************************************************************************
#ifndef __CQCUBE_H__
#define __CQCUBE_H__

#include "CQPrefab.h"

NS_CQ_BEGIN

class CQCube : public CQPrefab
{
public:
	CQCube();

	virtual ~CQCube();

public:
	SubMesh * genGeoData(float _side);
};

NS_CQ_END

#endif /* __CQCUBE_H__ */