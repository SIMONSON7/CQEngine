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

enum class MColorType
{
	NONE = 0X0,
	AMBIENT,
	DIFFUSE,
	SPECULAR,
	OPACITY,
	TRANSPARENCY,
	EMISSIVE,
};

enum class MTexType
{
	NONE = 0X0,
	AMBIENT,
	DIFFUSE,
	SPECULAR,
	NORMAL,
	HEIGHT,
	ROUGH,
};

class CQMaterial
{
public:
	typedef Vector4 Color;

public:
	CQMaterial();

	virtual ~CQMaterial();

public:
	inline void setProgram(CQShaderProgram * _program) { CQASSERT(_program); program_ = _program; }

	inline CQShaderProgram * getProgram() const { return program_; }

	void setColor(MColorType _type, Color _color);

	void setTex(MTexType _type, CQTexture* _tex);

	Color getColor(MColorType _type) const;

	CQTexture * getTex(MTexType _type) const;

private:
	CQShaderProgram * program_;

	Color ambientColor_;

	Color diffuseColor_;
	
	Color specularColor_;

	CQTexture * ambientTex_;

	CQTexture * diffuseTex_;

	CQTexture * specularTex_;

	CQTexture * normalTex_;

	CQTexture * heightTex_;

	CQTexture * roughTex_;

};

NS_CQ_END

#endif /* __CQMATERIAL_H__ */




