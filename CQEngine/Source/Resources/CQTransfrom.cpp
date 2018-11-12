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

void CQTransform::setLocalPos(const float3& _worldPos)
{
	localPos_ = _worldPos;
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

Matrix4& CQTransform::lookAt(float3 _worldTarget, float3 _worldPos, float3 _worldUp)
{
	front_ = normalize(_worldPos - _worldTarget);
	float3 u = normalize(_worldUp);
	right_ = normalize(cross(front_, u));
	up_ = cross(right_, front_);

	Matrix4 res(1);
	res[0][0] = right_.x;
	res[1][0] = right_.y;
	res[2][0] = right_.z;
	res[0][1] = up_.x;
	res[1][1] = up_.y;
	res[2][1] = up_.z;
	res[0][2] = -front_.x;
	res[1][2] = -front_.y;
	res[2][2] = -front_.z;
	res[3][0] = -dot(right_, _worldTarget);
	res[3][1] = -dot(up_, _worldTarget);
	res[3][2] = dot(front_, _worldTarget);
	return res;
}