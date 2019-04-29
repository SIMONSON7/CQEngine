#include <stb/stb_image.h>
#include "CQMemory.h"
#include "CQImg.h"
#include "CQResLoader.h"
#include "CQTexture.h"

USING_NS_CQ

CQTexture::CQTexture()
	:
	type_(TexMapType::D2),
	img_(nullptr)
{

}

CQTexture::~CQTexture()
{

}
