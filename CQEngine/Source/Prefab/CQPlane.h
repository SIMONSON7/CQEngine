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
	virtual void setupGeometry(CQMesh * _mesh);

	virtual void setupSurface(CQMaterial * _mat);

private:
	SubMesh * __genGeoData(float xsize, float zsize, int xdivs, int zdivs, float smax = 1.0F, float tmax = 1.0F);


};

NS_CQ_END

#endif /* __CQPLANE_H__ */