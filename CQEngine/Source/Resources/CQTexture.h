//*****************************************************************************
//
//! \file CQTexture.h
//! \brief 
//! \author qiu_hao
//! \date 2019/01/29 02:29.pm
//
//*****************************************************************************
#ifndef __CQTEXTURE_H__
#define __CQTEXTURE_H__

#include "CQMacros.h"
#include "CQResI.h"
#include "ResID.h"
#include "CQNoncopyable.h"

NS_CQ_BEGIN

enum class TexMapType
{
	D0, // NONE
	D1,	// Rendering line. Rain effect.
	D2, // Default
	D3, // Volume Textures
	CUBE, 
};

enum class TexWrapMode
{
	REPEAT,
	CLAMP,
};

enum class TexFilterMode
{
	POINT, // None
	BILLINEAR,
	TRILINEAR,
};

class CQImg;

class CQTexture
{
public:
	CQTexture();

	virtual ~CQTexture();

public:
	inline TexMapType getTexMapType() const { return type_; }

	inline void setRawImg(CQImg * _img) { img_ = _img; };

	inline CQImg * getRawImg() const { return img_; }

private:
	TexMapType type_;

	CQImg * img_;

};

NS_CQ_END

#endif /* __CQTEXTURE_H__ */