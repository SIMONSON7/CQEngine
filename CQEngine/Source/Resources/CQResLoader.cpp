#include <thread>
#include <stb/stb_image.h>
#include "CQIO.h"
#include "CQResLoader.h"

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

CQResLoader::ImgData *CQResLoader::loadImgDataAsync(const std::string& _filePath)
{
	return nullptr;
}

void CQResLoader::unloadImgData(ImgData * _data)
{
	CQASSERT(_data);
	stbi_image_free(_data->data_);
	CQ_FREE(_data);
}

