#include <thread>
#include <stb/stb_image.h>
#include "CQResLoader.h"
#include "CQIO.h"
#include "CQUtils.h"
#include "CQTexture.h"
#include "CQMesh.h"

USING_NS_CQ;

CQResLoader *CQResLoader::shareLoader()
{
	static CQResLoader s_resLoader;
	return &s_resLoader;
}

CQResLoader::~CQResLoader()
{
	if (asyncDCHd_)
	{
		cancelDelayCall(asyncDCHd_);
	}
}

CQResLoader::CQResLoader()
	:
	asyncDCHd_(0)
{

}

RawData * CQResLoader::loadRawDataSync(const std::string & _abPath)
{
	auto data = CQIO::cvLoadFile(_abPath);

	RawData * rData = (RawData*)CQ_MALLOC(sizeof(RawData));
	rData->data_ = (unsigned char*)CQ_MALLOC(data->size_);

	if (data->staus_ == Data::LOAD_SUCCESS)
	{
		rData->size_ = data->size_;
		::memcpy(rData->data_, data->buff_, data->size_);
	}

	CQIO::unloadFile(data);
	return rData;
}

void CQResLoader::unloadRawData(RawData * _data)
{
	CQASSERT(_data);
	CQ_FREE(_data->data_);
	_data->size_ = 0;
	CQ_FREE(_data);
}

void CQResLoader::loadRawDataAsync(const std::string & _abPath, std::function<void(RawData*)> & _cb)
{
	RawData* data = nullptr;

	// Lazy init.
	if (rdLoadThd_ == nullptr)
	{
		rdLoadThd_ = std::make_shared<std::thread>(&CQResLoader::__rdLoadThreadFun, this);
	}

	if (asyncDCHd_ == 0)
	{
		asyncDCHd_ = delayCall(makeAction(&CQResLoader::__doCallBack, this), 0, true);
	}

	// Create.
	AsyncRawData * asyncData = CQ_NEW(AsyncRawData);
	asyncData->cb_ = _cb;
	asyncData->rawData_ = data;
	asyncData->abPath_ = _abPath;

	asyncStack_.push(asyncData);
}

// Threads dedicated to loading pictures continuously.
void CQResLoader::__rdLoadThreadFun()
{
	AsyncRawData *data = nullptr;

	while (true)
	{
		asyncStack_.wait_and_pop(data);

		data->rawData_= loadRawDataSync(data->abPath_);

		cbStack_.push(data);
	}
}

void CQResLoader::__doCallBack()
{
	AsyncRawData *data = nullptr;
	
	if (cbStack_.try_pop(data))
	{
		if (data->cb_)
		{
			data->cb_(data->rawData_);
		}

		// User responsible for release the rawData.
		//unloadImgData(data->imgData_);
		CQ_DELETE(data, AsyncRawData);
	}
}

Img * CQResLoader::loadImgSync(const std::string & _abPath)
{
	auto img = (Img*)CQ_MALLOC(sizeof(Img));
	int nrComponents;

	// flip textures y coordinate
	stbi_set_flip_vertically_on_load(true);
	img->data_ = stbi_load(_abPath.c_str(), &(img->width_), &(img->height_), &nrComponents, 0);
	switch (nrComponents)
	{
	case 1:
		img->format_ = Img::Format::RED;
		break;
	case 3:
		img->format_ = Img::Format::RGB;
		break;
	case 4:
		img->format_ = Img::Format::RGBA;
		break;
	default:
		img->format_ = Img::Format::NONE;
		break;
	}

	return img;
}

void CQResLoader::unloadImg(Img * _img)
{
	if (_img)
	{
		stbi_image_free(_img->data_);
		CQ_FREE(_img);
	}
}

std::vector<SubMesh*> CQResLoader::loadSubMeshesSync(const std::string & _abPath)
{
	std::vector<SubMesh*> subMeshes;

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(_abPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		return subMeshes;
	}

	auto root = scene->mRootNode;
	__recursiveProcessNode(root, scene, &subMeshes);

	return subMeshes;
}

void CQResLoader::unloadMesh(SubMesh * _mesh)
{
	if (_mesh)
	{
		CQ_DELETE(_mesh, SubMesh);
	}
}

void CQResLoader::__recursiveProcessNode(aiNode * _node, const aiScene * _scene, std::vector<SubMesh*> * _subMeshes)
{
	for (unsigned int i = 0; i < _node->mNumMeshes; ++i)
	{
		aiMesh * mesh = _scene->mMeshes[_node->mMeshes[i]];
		_subMeshes->push_back(__processSubMesh(mesh));
	}

	for (unsigned int i = 0 ; i < _node->mNumChildren; ++i)
	{
		__recursiveProcessNode(_node->mChildren[i], _scene, _subMeshes);
	}
}

SubMesh * CQResLoader::__processSubMesh(aiMesh * _mesh)
{
	SubMesh* subMesh = CQ_NEW(SubMesh);

	// Vertex
	for (unsigned int i = 0; i < _mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		// pos
		vertex.pos_.x = _mesh->mVertices[i].x;
		vertex.pos_.y = _mesh->mVertices[i].y;
		vertex.pos_.z = _mesh->mVertices[i].z;

		// normal
		vertex.normal_.x = _mesh->mNormals[i].x;
		vertex.normal_.y = _mesh->mNormals[i].y;
		vertex.normal_.z = _mesh->mNormals[i].z;

		// uv
		if (_mesh->mTextureCoords[0])
		{
			vertex.uv_.x = _mesh->mTextureCoords[0][i].x;
			vertex.uv_.y = _mesh->mTextureCoords[0][i].y;
		}

		subMesh->vBuff_.push_back(vertex);
	}

	// Index
	// face == triangle
	for (unsigned int i = 0; i < _mesh->mNumFaces; i++)
	{
		aiFace face = _mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			subMesh->iBuff_.push_back(face.mIndices[j]);
		}
	}

	return subMesh;
}




