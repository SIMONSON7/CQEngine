#include <stb/stb_image.h>
#include "CQMemory.h"
#include "CQImg.h"
#include "CQResLoader.h"
#include "CQTexture.h"
#include "CQDebug.h"

USING_NS_CQ

CQTexture::CQTexture()
	:
	img_(nullptr),
	isMipMap_(true),
	type_(TexMapType::D2),
	texId_(0)
{
	
}

CQTexture::CQTexture(CQImg * _img)
	:
	isMipMap_(true),
	type_(TexMapType::D2)
{
	if (_img)
	{
		img_ = _img;
		genTexHandle();
	}
}

CQTexture::~CQTexture()
{

}

void CQTexture::genTexHandle(bool _isMipMap,
	TexMapType _mapType,
	TexWrapMode _warpMode,
	TexFilterMode _filterMode)
{
	if (img_)
	{
		CQ_GLCHECK(glGenTextures(1, &texId_));

		bind();
		{
			// TODO:
			CQ_GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			CQ_GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
			CQ_GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			CQ_GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

			CQ_GLCHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_->getWidth(), img_->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, img_->getData()));
			if (isMipMap_)
			{
				CQ_GLCHECK(glGenerateMipmap(GL_TEXTURE_2D));
			}
		}
		unbind();
	}
}

void CQTexture::bind(int _stage)
{
	CQ_GLCHECK(glActiveTexture(GL_TEXTURE0 + _stage));
	CQ_GLCHECK(glBindTexture(GL_TEXTURE_2D, texId_));
}

void CQTexture::unbind()
{
	CQ_GLCHECK(glBindTexture(GL_TEXTURE_2D, 0));
}
