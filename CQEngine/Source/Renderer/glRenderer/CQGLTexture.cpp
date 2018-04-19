#include "CQGLTexture.h"
#include "CQDebug.h"

USING_NS_CQ;

CQGLTexture::CQGLTexture(int _width, int _height, void *_data)
	:
	width_(_width),
	height_(_height),
	data_(_data)
{
	CQ_GLCHECK(glGenTextures(1, &textureID_));

	CQ_GLCHECK(glActiveTexture(GL_TEXTURE0)); // option : for multi texture	
	CQ_GLCHECK(glBindTexture(GL_TEXTURE_2D, textureID_));
	{
		CQ_GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		CQ_GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		CQ_GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		CQ_GLCHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		CQ_GLCHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data_));
	}
	CQ_GLCHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

CQGLTexture::~CQGLTexture() {}

void CQGLTexture::Bind(int _stage)
{
	CQ_GLCHECK(glActiveTexture(GL_TEXTURE0 +_stage));
	CQ_GLCHECK(glBindTexture(GL_TEXTURE_2D, textureID_));
}

void CQGLTexture::Unbind()
{
	CQ_GLCHECK(glBindTexture(GL_TEXTURE_2D, 0));
}


