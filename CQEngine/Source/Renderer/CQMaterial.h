//*****************************************************************************
//
//! \file CQMaterial.h
//! \brief 
//! \author qiu_hao
//! \date 2019/02/11 02:22.pm
//
//*****************************************************************************
#ifndef __CQMATERIAL_H__
#define __CQMATERIAL_H__

#include "CQMacros.h"
#include "CQMath.h"

NS_CQ_BEGIN

class CQTexture;
class CQShaderProgram;

enum MColorType
{
	MCOLORTYPE_NONE = 0X0,
	AMBIENT_COLOR,
	DIFFUSE_COLOR,
	SPECULAR_COLOR,
	OPACITY_COLOR,
	TRANSPARENCY_COLOR,
	EMISSIVE_COLOR,
};

enum MTexType
{
	MTEXTYPE_NONE = 0X0,
	DIFFUSE_TEX,
	SPECULAR_TEX,
	NORMAL_TEX,
	HEIGHT_TEX,
	ROUGH_TEX,
};

class CQMaterial
{
public:
	typedef Vector4 Color;

public:
	CQMaterial();

	virtual ~CQMaterial();

public:
	void setColor(MColorType _type, Color _color);

	void setTex(MTexType _type, CQTexture* _tex);

private:
	CQShaderProgram * program_;

	Color ambientColor_;

	Color diffuseColor_;
	
	Color specularColor_;

	CQTexture * diffuseTex_;

	CQTexture * specularTex_;

	CQTexture * normalTex_;

	CQTexture * heightTex_;

	CQTexture * roughTex_;

};

NS_CQ_END

#endif /* __CQMATERIAL_H__ */




