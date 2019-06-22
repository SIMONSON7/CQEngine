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
	typedef unsigned int TextureHandle;

public:
	CQTexture();

	CQTexture(CQImg * _img);

	virtual ~CQTexture();

public:
	void genTexHandle(bool _isMipMap = true,
		bool _isRGBA = false,
		TexMapType _mapType = TexMapType::D2,
		TexWrapMode _warpMode = TexWrapMode::REPEAT,
		TexFilterMode _filterMode = TexFilterMode::POINT);

	void bind(int _stage = 0);

	void unbind();

public:
	inline const bool getIsMipMap() const { return isMipMap_; }

	inline TextureHandle getTexHandle() { return texId_; }

	inline TexMapType getTexMapType() const { return type_; }

	// TODO:
	//inline TexWrapMode getTexWrapMode() const {}

	//inline TexFilterMode getTexFilterMode() const {}

	inline void setRawImg(CQImg * _img) { img_ = _img; };

	inline CQImg * getRawImg() const { return img_; }

private:
	CQImg * img_;

	bool isMipMap_;

	TexMapType type_;

	TextureHandle texId_;
};

NS_CQ_END

#endif /* __CQTEXTURE_H__ */



