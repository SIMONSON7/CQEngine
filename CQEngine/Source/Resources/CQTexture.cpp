#include <stb/stb_image.h>
#include "CQTexture.h"
#include "CQResLoader.h"

USING_NS_CQ

CQTexture::CQTexture()
	:
	resID_(ResID::INVALID),
	type_(TexMapType::D2),
	img_(nullptr)
{

}

CQTexture::~CQTexture()
{
	onDestory();
}

void CQTexture::onLoadDiskRes(const std::string & _abPath)
{
	img_ = CQResLoader::shareLoader()->loadImgSync(_abPath);
}

void CQTexture::onDestory()
{
	CQResLoader::shareLoader()->unloadImg(img_);
}