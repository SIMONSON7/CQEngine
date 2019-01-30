#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "CQMesh.h"

USING_NS_CQ

CQMesh::CQMesh()
	:
	resID_(ResID::INVALID)
{

}

CQMesh::~CQMesh()
{

}

void CQMesh::onLoadDiskRes(const std::string & _abPath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(_abPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		return;
	}

	auto root = scene->mRootNode;
	for (int i = 0 ; i < root->mNumMeshes; ++i)
	{
		aiMesh * mesh = scene->mMeshes[root->mMeshes[i]];
		sharedMesh_.push_back(processSubMesh(mesh));
	}
}

SubMesh * processSubMesh(aiMesh * mesh)
{

}

void tmpProcessMesh()
{

}

void CQMesh::onDestory()
{

}