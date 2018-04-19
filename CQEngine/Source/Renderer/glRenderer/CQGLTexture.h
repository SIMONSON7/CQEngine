/*
*
*		qiu_hao		2018/03/08		05:18.pm
*/
#ifndef __CQGLTEXTURE_H__
#define __CQGLTEXTURE_H__

#include <glad/glad.h>
#include "CQMacros.h"
//#include "CQObject.h"
//#include <map>

NS_CQ_BEGIN

// TODO £ºIt's just a rough package now.
// Open more interfaces in the future.
class CQGLTexture 
{
public:
	CQGLTexture(int _width, int _height, void *_data);
	virtual ~CQGLTexture();
public:
	const unsigned int GetTextureID() const;
public:
	void Bind();
	void Unbind();
private:
	unsigned int textureID_;
	int width_;
	int height_;
	void *data_;

	//typedef std::map<TextureID, CQTexture*> TextureIDMap;
	//static TextureIDMap s_textureIDMap;
};

NS_CQ_END

#endif /*__CQGLTEXTURE_H__*/
