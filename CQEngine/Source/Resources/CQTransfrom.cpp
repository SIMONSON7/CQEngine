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

CQTransform::CQTransform(const CQTransform & other)
{
	//this->scale_ = other.getScale();
	//this->localPos_ = other.getLocalPos();

	//Vector3 scale_;
	//Vector3 localPos_;
	//Vector3 worldPos_;
	//Vector3 eulerRot_;
	//Quaternion quatrRot_;

	//// Local coordinate system.
	//Vector3 up_;
	//Vector3 right_;
	//Vector3 target_;/* FRONT = POS - TARGET */
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

void CQTransform::setWorldPos(const Vector3& _pos)
{
	worldPos_ = _pos;
	lookAt(target_, worldPos_, up_);
}

void CQTransform::setRotEuler(const Vector3& _rot)
{
	eulerRot_ = _rot;
	quaternion* q = CQ_NEW(quaternion, _rot);
	quatrRot_ = *q;
	CQ_DELETE(q, quaternion);

	//auto angleRight = eulerRot_.x;
	//auto angleUp    = eulerRot_.y;
	//auto angleFront = eulerRot_.z;

	//up_ = rotate(angleRight, up_);

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

Vector3& CQTransform::getLocalPos()
{
	return localPos_;
}

Vector3& CQTransform::getWorldPos()
{
	return worldPos_;
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

Vector3& CQTransform::getFront()
{
	return normalize(worldPos_ - target_);
}

Vector3& CQTransform::getUp()
{
	return up_;
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
	Vector3 front = getFront();
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
	Vector3 front = getFront();
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