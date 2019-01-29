#include <stb/stb_image.h>
#include "CQTexture.h"

USING_NS_CQ

CQTexture::CQTexture()
	:
	resID_(ResID::INVALID),
	type_(TexType::D2),
	width_(0),
	height_(0),
	data_(nullptr)
{

}

CQTexture::~CQTexture()
{
	onDestory();
}

void CQTexture::onLoadDiskRes(const std::string & _abPath)
{
	int nrComponents;

	// flip textures y coordinate
	stbi_set_flip_vertically_on_load(true);
	data_ = stbi_load(_abPath.c_str(), &width_, &height_, &nrComponents, 0);
}

void CQTexture::onDestory()
{
	stbi_image_free(data_);
	data_ = nullptr;
}