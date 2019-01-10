#include "CQTransform.h"
#include "CQMemory.h"

USING_NS_CQ;

CQTransform::CQTransform()
	:
	up_(0, 1, 0),
	right_(1, 0, 0),
	scale_(1, 1, 1),
	worldPos_(0, 0, 0),
	eulerRot_(0, 0, 0),
	toLocalMat_(1)
{
	name_ = "Transform";
}

CQTransform::~CQTransform()
{

}

CQTransform::CQTransform(const CQTransform & other)
{
	__setTransform(other);
}

CQTransform& CQTransform::operator=(const CQTransform & other)
{
	__setTransform(other);
	return *this;
}

void CQTransform::setLocalPos(const Vector3& _pos)
{
	localPos_ = _pos;
}

void CQTransform::setWorldPos(const Vector3& _pos)
{
	worldPos_ = _pos;
	lookAt(worldPos_, target_, up_);
}

void CQTransform::setRotEuler(const Vector3& _rot)
{
	eulerRot_ = _rot;
	quaternion q(_rot);
	quatrRot_ = q;

	auto rotMat = mat4_cast(quatrRot_);
	up_		= up_ * rotMat;
	right_	= right_ * rotMat;
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
	return normalize(cross(right_, up_));
}

Vector3& CQTransform::getUp()
{
	return up_;
}

void CQTransform::lookAt(Vector3 _worldPos, Vector3 _worldTargetPos, Vector3 _worldUp)
{
	worldPos_		= _worldPos;
	target_			= _worldTargetPos;
	Vector3 front	= normalize(target_ - worldPos_);
	Vector3 u		= normalize(_worldUp);
	right_			= normalize(cross(front, u));
	up_				= cross(right_, front);
}

Matrix4& CQTransform::calWorldToLcalMatRH()
{
	Vector3 front = normalize(target_ - worldPos_);
	toLocalMat_[0][0] =  right_.x;
	toLocalMat_[1][0] =  right_.y;
	toLocalMat_[2][0] =  right_.z;
	toLocalMat_[0][1] =  up_.x;
	toLocalMat_[1][1] =  up_.y;
	toLocalMat_[2][1] =  up_.z;
	toLocalMat_[0][2] = -front.x;
	toLocalMat_[1][2] = -front.y;
	toLocalMat_[2][2] = -front.z;
	toLocalMat_[3][0] = -dot(right_, worldPos_);
	toLocalMat_[3][1] = -dot(up_,    worldPos_);
	toLocalMat_[3][2] =  dot(front,  worldPos_);
	return toLocalMat_;
}

Matrix4& CQTransform::calWorldToLcalMatLH()
{
	Vector3 front = normalize(target_ - worldPos_);
	toLocalMat_[0][0] =  right_.x;
	toLocalMat_[1][0] =  right_.y;
	toLocalMat_[2][0] =  right_.z;
	toLocalMat_[0][1] =  up_.x;
	toLocalMat_[1][1] =  up_.y;
	toLocalMat_[2][1] =  up_.z;
	toLocalMat_[0][2] =  front.x;
	toLocalMat_[1][2] =  front.y;
	toLocalMat_[2][2] =  front.z;
	toLocalMat_[3][0] = -dot(right_, worldPos_);
	toLocalMat_[3][1] = -dot(up_,    worldPos_);
	toLocalMat_[3][2] = -dot(front,  worldPos_);
	return toLocalMat_;
}

void CQTransform::__setTransform(const CQTransform & other)
{
	this->scale_ = other.scale_;
	this->localPos_ = other.localPos_;
	this->worldPos_ = other.worldPos_;
	this->eulerRot_ = other.eulerRot_;
	this->quatrRot_ = other.quatrRot_;

	this->up_ = other.up_;;
	this->right_ = other.right_;
	this->target_ = other.target_;

	this->toLocalMat_ = other.toLocalMat_;
}
