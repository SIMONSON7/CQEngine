#include "CQMemory.h"
#include "CQMesh.h"
#include "CQResLoader.h"

USING_NS_CQ

CQMesh::CQMesh()
	:
	resID_(ResID::INVALID)
{
	meshes_.clear();
}

CQMesh::~CQMesh()
{
	onDestory();
}

void CQMesh::onLoadDiskRes(const std::string & _abPath)
{
	meshes_ = CQResLoader::shareLoader()->loadSubMeshesSync(_abPath);
}

void CQMesh::onDestory()
{
	auto loader = CQResLoader::shareLoader();
	for each (auto subMesh in meshes_)
	{
		loader->unloadMesh(subMesh);
	}

	meshes_.clear();
}