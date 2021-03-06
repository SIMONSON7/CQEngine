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

struct SubMesh;

class CQPlane : public CQPrefab
{
public:
	CQPlane();

	virtual ~CQPlane();

public:
	SubMesh * genGeoData(float _xsize, float _zsize, int _xdivs, int _zdivs, float _smax = 1.0F, float _tmax = 1.0F);
};

NS_CQ_END

#endif /* __CQPLANE_H__ */