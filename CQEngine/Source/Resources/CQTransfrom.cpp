#include "CQTransform.h"
#include "CQMemory.h"

USING_NS_CQ;

CQTransform::CQTransform()
	:
	scale_(1, 1, 1),
	up_(0, 1, 0)
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

void CQTransform::setLocalPos(const Vector3& _pos)
{
	localPos_ = _pos;
}

void CQTransform::setRotEuler(const Vector3& _rot)
{
	eulerRot_ = _rot;
	quaternion* q = CQ_NEW(quaternion, _rot);
	quatrRot_ = *q;
	CQ_DELETE(q, quaternion);
}

void CQTransform::setRotQuart(const Quaternion& _quart)
{
	quatrRot_ = _quart;
	eulerRot_ = eulerAngles(_quart);
}

void CQTransform::setScale(const Vector3& _scale)
{
	scale_ = _scale;
}

Vector3& CQTransform::getPos()
{
	return localPos_;
}

Vector3& CQTransform::getRotEuler()
{
	return eulerRot_;
}

quaternion& CQTransform::getRotQuart()
{
	return quatrRot_;
}

Vector3& CQTransform::getScale()
{
	return scale_;
}

void CQTransform::lookAt(Vector3 _worldTarget, Vector3 _worldPos, Vector3 _worldUp)
{
	target_			= _worldTarget;
	worldPos_		= _worldPos;
	Vector3 front	= normalize(worldPos_ - target_);
	Vector3 u		= normalize(_worldUp);
	right_			= normalize(cross(front, u));
	up_				= cross(right_, front);
}

Matrix4& CQTransform::calWorldToLcalMatRH()
{
	Vector3 front = normalize(worldPos_ - target_);
	Matrix4 res(1);
	res[0][0] =  right_.x;
	res[1][0] =  right_.y;
	res[2][0] =  right_.z;
	res[0][1] =  up_.x;
	res[1][1] =  up_.y;
	res[2][1] =  up_.z;
	res[0][2] = -front.x;
	res[1][2] = -front.y;
	res[2][2] = -front.z;
	res[3][0] = -dot(right_, target_);
	res[3][1] = -dot(up_,    target_);
	res[3][2] =  dot(front,  target_);
	return res;
}

Matrix4& CQTransform::calWorldToLcalMatLH()
{
	Vector3 front = normalize(worldPos_ - target_);
	Matrix4 res(1);
	res[0][0] =  right_.x;
	res[1][0] =  right_.y;
	res[2][0] =  right_.z;
	res[0][1] =  up_.x;
	res[1][1] =  up_.y;
	res[2][1] =  up_.z;
	res[0][2] =  front.x;
	res[1][2] =  front.y;
	res[2][2] =  front.z;
	res[3][0] = -dot(right_, target_);
	res[3][1] = -dot(up_,    target_);
	res[3][2] = -dot(front,  target_);
	return res;
}