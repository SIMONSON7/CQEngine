#include "CQMemory.h"
#include "CQSceneNode.h"
#include "CQMesh.h"
#include "CQMeshRenderer.h"
#include "CQPrefab.h"
#include "CQPlane.h"
#include "CQCube.h"
#include "CQPrefabFactory.h"

USING_NS_CQ

CQPrefab * CQPrefabFactory::createPlane(float _xsize, float _zsize, int _xdivs, int _zdivs, float _smax, float _tmax)
{
	CQPlane * plane = CQ_NEW(CQPlane);
	auto mesh = CQ_NEW(CQMesh);
	mesh->sharedMesh().push_back(plane->genGeoData(_xsize, _zsize, _xdivs, _zdivs, _smax, _tmax));
	auto mr = std::dynamic_pointer_cast<CQMeshRenderer>(plane->getSceneNode()->getObj()->getComponentByName("MeshRender"));
	mr->setGeometryData(mesh);
	return plane;
}

CQPrefab * CQPrefabFactory::createCube(float _side)
{
	CQCube * cube = CQ_NEW(CQCube);
	auto mesh = CQ_NEW(CQMesh);
	mesh->sharedMesh().push_back(cube->genGeoData(_side));
	auto mr = std::dynamic_pointer_cast<CQMeshRenderer>(cube->getSceneNode()->getObj()->getComponentByName("MeshRender"));
	mr->setGeometryData(mesh);
	return cube;
}

CQPrefab * CQPrefabFactory::createSphere()
{
	return nullptr;
}