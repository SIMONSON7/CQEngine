#include "CQTransform.h"

USING_NS_CQ;

CQTransform::CQTransform()
{

}

CQTransform::~CQTransform()
{

}

CQTransform::CQTransform(const CQTransform &)
{

}

CQTransform& CQTransform::operator=(const CQTransform &)
{
	return *this;
}

const std::string& CQTransform::getName() const
{
	return "Transform";
}

void CQTransform::setPos(const float3& _pos)
{

}

void CQTransform::setRotEuler(const float3& _rot)
{

}

void CQTransform::setRotQuart(const quaternion& _quart)
{

}

void CQTransform::setScale(const float3& _scale)
{

}

float3& CQTransform::getPos()
{
	return *(new float3());
}

float3& CQTransform::getRotEuler()
{
	return *(new float3());
}

quaternion& CQTransform::getRotQuart()
{
	return *(new quaternion());
}

float3& CQTransform::getScale()
{
	return *(new float3());
}