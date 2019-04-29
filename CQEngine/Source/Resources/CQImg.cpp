#include <stb/stb_image.h>
#include "CQResLoader.h"
#include "CQImg.h"

USING_NS_CQ

CQImg::CQImg()
	:
	resID_(ResID::INVALID),
	width_(0),
	height_(0),
	format_(CQImg::Format::NONE),
	data_(nullptr)
{

}

CQImg::~CQImg()
{
	onDestory();
}

void CQImg::onLoadDiskRes(const std::string & _abPath)
{
	int nrComponents;
	CQResLoader::shareLoader()->loadImgSync(_abPath, data_, &width_, &height_, &nrComponents);
	switch (nrComponents)
	{
	case 1:
		format_ = CQImg::Format::RED;
		break;
	case 3:
		format_ = CQImg::Format::RGB;
		break;
	case 4:
		format_ = CQImg::Format::RGBA;
		break;
	default:
		format_ = CQImg::Format::NONE;
		break;
	}
}

void CQImg::onDestory()
{
	CQResLoader::shareLoader()->unloadImg(data_);
}