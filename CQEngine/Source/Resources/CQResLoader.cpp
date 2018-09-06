#include <thread>
#include <stb/stb_image.h>
#include "CQResLoader.h"
#include "CQUtils.h"

USING_NS_CQ;

CQResLoader *CQResLoader::shareLoader()
{
	static CQResLoader s_resLoader;
	return &s_resLoader;
}

CQResLoader::ImgData *CQResLoader::loadImgDataSync(const std::string& _filePath)
{
	ImgData *imgData = (ImgData*)CQ_MALLOC(sizeof(ImgData));
	int w, h, nrComponents;

	// flip textures y coordinate
	stbi_set_flip_vertically_on_load(true);
	imgData->data_ = stbi_load(CQIO::searchFullPath(_filePath).c_str(), &w, &h, &nrComponents, 0);
	imgData->type_ = nrComponents;
	imgData->width_ = w;
	imgData->height_ = h;

	return imgData;
}

void CQResLoader::unloadImgData(ImgData * _data)
{
	CQASSERT(_data);
	stbi_image_free(_data->data_);
	CQ_FREE(_data);
}

void CQResLoader::loadImgDataAsync(const std::string& _filePath, Action& _cb)
{
	// check cache.

	// lazy init.
	if (texLoadThd_ == nullptr)
	{
		texLoadThd_ = std::make_shared<std::thread>(&CQResLoader::loadImg, this);
	}

	// 
	if (checkHd_ == 0)
	{
		delayCall(makeAction(&CQResLoader::checkLoadedImg, this), 0, true);
	}


	
}

// creator.
void CQResLoader::loadImg()
{




}

// consumer.
void CQResLoader::checkLoadedImg()
{


}




