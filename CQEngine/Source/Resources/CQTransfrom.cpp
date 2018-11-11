#include "CQTransform.h"
#include "CQMemory.h"

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

void CQTransform::setLocalPos(const float3& _pos)
{
	localPos_ = _pos;
}

void CQTransform::setRotEuler(const float3& _rot)
{
	eulerRot_ = _rot;
	quaternion* q = CQ_NEW(quaternion, _rot);
	quatrRot_ = *q;
	CQ_DELETE(q, quaternion);
}

void CQTransform::setRotQuart(const quaternion& _quart)
{
	quatrRot_ = _quart;
	eulerRot_ = eulerAngles(_quart);
}

void CQTransform::setScale(const float3& _scale)
{
	scale_ = _scale;
}

float3& CQTransform::getPos()
{
	return localPos_;
}

float3& CQTransform::getRotEuler()
{
	return eulerRot_;
}

quaternion& CQTransform::getRotQuart()
{
	return quatrRot_;
}

float3& CQTransform::getScale()
{
	return scale_;
}