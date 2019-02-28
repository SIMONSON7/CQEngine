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
#include "CQObject.h"

NS_CQ_BEGIN;

enum class LightType
{
	NONE = 0,
	POINT,
	SPOT,
	DIRECTIONAL
};

class CQLight /*: public CQObject*/
{
public:
	explicit CQLight() = default;

	~CQLight() = default;

public:
	inline LightType getLightType() { return type_; }

	inline void  setLightType(LightType _type) { type_ = _type; }


private:
	LightType type_;

};

class CQPointLight : public CQLight
{


private:
	
};

class CQSpotLight : public CQLight
{

};

class CQDirectionalLight : public CQLight
{

};

NS_CQ_END;

#endif /* __CQLIGHT_H__ */

