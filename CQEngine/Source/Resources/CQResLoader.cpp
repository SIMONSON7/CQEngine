#include "CQMemory.h"
#include "CQResLoader.h"
#include "CQResLoader.h"
#include <stb/stb_image.h>
#include <type_traits>

USING_NS_CQ;

CQResLoader * CQResLoader::shareLoader()
{
	static CQResLoader s_resLoader;
	return &s_resLoader;
}

CQResLoader::ImgData * CQResLoader::loadImgDataSync(const char *_imgPath)
{
	ImgData *imgData= CQ_NEW(ImgData);
	int w, h, nrComponents;

	// flip textures y coordinate
	stbi_set_flip_vertically_on_load(true);
	imgData->data_ = stbi_load(_imgPath, &w, &h, &nrComponents, 0);
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

template<typename T>
void foo()
{
	typedef typename std::decay<T>::type U;
	U *u_ptr = new U();
	// ...

	std::ref()
}
