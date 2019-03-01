#include "CQLight.h"

USING_NS_CQ;

CQLight::CQLight(LightType _type, ColorIntensity _color)
	:
	type_(_type),
	color_(_color)
{
	
}

CQPointLight::CQPointLight(LightType _type, ColorIntensity _color, Vector4 _pos)
	:
	CQLight(_type, _color),
	pos_(_pos)
{

}