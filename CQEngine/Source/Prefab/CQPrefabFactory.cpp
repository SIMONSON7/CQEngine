#include "CQMemory.h"
#include "CQPrefab.h"
#include "CQPlane.h"
#include "CQCube.h"
#include "CQPrefabFactory.h"

USING_NS_CQ

CQPrefab * CQPrefabFactory::createPlane(float _xsize, float _zsize, int _xdivs, int _zdivs, float _smax, float _tmax)
{
	CQPlane * plane = CQ_NEW(CQPlane);
	plane->genGeoData(_xsize, _zsize, _xdivs, _zdivs, _smax, _tmax);
	return plane;
}

CQPrefab * CQPrefabFactory::createCube(float _side)
{
	CQCube * cube = CQ_NEW(CQCube);
	cube->genGeoData(_side);
	return cube;
}

CQPrefab * CQPrefabFactory::createSphere()
{
	return nullptr;
}