#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "CQMesh.h"
#include "CQMemory.h"

USING_NS_CQ

CQMesh::CQMesh()
	:
	resID_(ResID::INVALID)
{

}

CQMesh::~CQMesh()
{

}

extern SubMesh* processSubMesh(aiMesh* mesh);

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

SubMesh* processSubMesh(aiMesh* mesh)
{
	SubMesh* subMesh = CQ_NEW(SubMesh);

	// Vertex
	for (int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		// pos
		vertex.pos_.x = mesh->mVertices[i].x;
		vertex.pos_.y = mesh->mVertices[i].y;
		vertex.pos_.z = mesh->mVertices[i].z;
		
		// normal
		vertex.normal_.x = mesh->mNormals[i].x;
		vertex.normal_.y = mesh->mNormals[i].y;
		vertex.normal_.z = mesh->mNormals[i].z;
		
		// uv
		if (mesh->mTextureCoords[0])
		{
			vertex.uv_.x = mesh->mTextureCoords[0][i].x;
			vertex.uv_.y = mesh->mTextureCoords[0][i].y;
		}

		subMesh->vBuff_.push_back(vertex);
	}

	// Index
	// face == triangle
	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
		{
			subMesh->iBuff_.push_back(face.mIndices[j]);
		}
	}

	return subMesh;
}

void CQMesh::onDestory()
{

}