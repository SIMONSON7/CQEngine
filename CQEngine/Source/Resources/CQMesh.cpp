#include "CQMesh.h"
#include "CQResLoader.h"

USING_NS_CQ

CQMesh::CQMesh()
	:
	resID_(ResID::INVALID)
{

}

CQMesh::~CQMesh()
{
	onDestory();
}

void CQMesh::onLoadDiskRes(const std::string & _abPath)
{
	sharedMesh_ = CQResLoader::shareLoader()->loadSubMeshesSync(_abPath);
}

void CQMesh::onDestory()
{
	auto loader = CQResLoader::shareLoader();
	for each (auto subMesh in sharedMesh_)
	{
		loader->unloadMesh(subMesh);
	}
}