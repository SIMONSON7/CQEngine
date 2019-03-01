//*****************************************************************************
//
//! \file CQLight.h
//! \brief 
//! \author qiu_hao
//! \date 2019/02/14 10:28.pm
//
//*****************************************************************************
#ifndef __CQLIGHT_H__
#define __CQLIGHT_H__

#include "CQMacros.h"
#include "CQMath.h"

NS_CQ_BEGIN;

enum class LightType
{
	NONE = 0,
	POINT,
	SPOT,
	DIRECTIONAL
};

class CQLight 
{
public:
	typedef Vector3 ColorIntensity;

public:
	explicit CQLight() = default;

	virtual ~CQLight() = default;

	CQLight(LightType _type, ColorIntensity _color);

public:
	inline LightType getLightType() const { return type_; }

	inline ColorIntensity getColor() const { return color_; }

	inline void  setLightType(LightType _type) { type_ = _type; }

	inline void  setColor(ColorIntensity _color) { color_ = _color; }

private:
	LightType type_;

	ColorIntensity color_;

};

class CQPointLight : public CQLight
{
public:
	explicit CQPointLight() = default;

	virtual ~CQPointLight() = default;

	CQPointLight(LightType _type, ColorIntensity _color, Vector4 _pos);

public:
	inline Vector4 getWorldPos() const { return pos_; }

	inline void setWorldPos(Vector4 _pos) { pos_ = _pos; }

private:
	Vector4 pos_;
};

class CQSpotLight : public CQLight
{

};

class CQDirectionalLight : public CQLight
{

};

NS_CQ_END;

#endif /* __CQLIGHT_H__ */

