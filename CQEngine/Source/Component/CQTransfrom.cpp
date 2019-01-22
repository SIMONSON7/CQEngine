#include "CQTransform.h"
#include "CQMemory.h"

USING_NS_CQ;

const Vector3 CQTransform::sWorldUp = Vector3(0, 1, 0);

const Vector3 CQTransform::sWorldRight = Vector3(1, 0, 0);

const Vector3 CQTransform::sWorldFront = Vector3(0, 0, 1);

const Vector3 CQTransform::sLocalPos = Vector3(0, 0, 0);

CQTransform::CQTransform()
	:
	parent_(nullptr),
	srtMat_(1),
	scale_(1.0f),
	relativePos_(0.0f),
	worldPos_(relativePos_),
	up_(sWorldUp),
	right_(sWorldRight),
	front_(sWorldFront),
	target_(0),
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

void CQTransform::setScale(const Vector3& _scale)
{
	scale_ = _scale;

	__updateModelMat();
}

Matrix4 CQTransform::getScaleMat()
{
	Matrix4 mat;
	auto scaleMat = mat.scale(scale_);
	return scaleMat;
}

void CQTransform::rot(const float angle, const Vector3& axis)
{
	rotQuatr_ = rotate(angle, axis);

	__updateAxis();
	__updateModelMat();
}

void CQTransform::rotateX(const float _angle)
{
	rot(_angle, sWorldRight);
}

void CQTransform::rotateY(const float _angle)
{
	rot(_angle, sWorldUp);
}

void CQTransform::rotateZ(const float _angle)
{
	rot(_angle, sWorldFront);
}

Matrix4 CQTransform::getTranslateMat()
{
	Matrix4 res;
	return translate(res, worldPos_);
}

void CQTransform::move(Vector3& _worldPos)
{
	moveTo(_worldPos - worldPos_);
}

void CQTransform::moveTo(Vector3& _worldOffset)
{
	// Root Node
	if (parent_ == nullptr)
	{
		relativePos_ += _worldOffset;
		worldPos_ = relativePos_;
	}
	// Non Root Node
	else
	{
		relativePos_ += _worldOffset;
		auto parentRotTransMat = parent_->getTranslateMat() * parent_->getRotMat();
		worldPos_ = relativePos_ * parentRotTransMat.inverse();
	}

	__updateModelMat();
}

void CQTransform::buildLocalCoordinate(Vector3& _worldPos, Vector3& _worldTargetPos, Vector3& _worldUp)
{
	target_		= _worldTargetPos;
	front_		= normalize(target_ - _worldPos);
	Vector3 u	= normalize(_worldUp);
	right_		= normalize(cross(front_, u));
	up_			= cross(right_, front_);

	move(_worldPos);
}

Matrix4& CQTransform::calWorldToLcalMatRH()
{
	Vector3 front = normalize(target_ - worldPos_);
	toLocalMat_[0][0] = right_.x;
	toLocalMat_[1][0] = right_.y;
	toLocalMat_[2][0] = right_.z;
	toLocalMat_[0][1] = up_.x;
	toLocalMat_[1][1] = up_.y;
	toLocalMat_[2][1] = up_.z;
	toLocalMat_[0][2] = -front.x;
	toLocalMat_[1][2] = -front.y;
	toLocalMat_[2][2] = -front.z;
	toLocalMat_[3][0] = -dot(right_, worldPos_);
	toLocalMat_[3][1] = -dot(up_, worldPos_);
	toLocalMat_[3][2] = dot(front, worldPos_);
	return toLocalMat_;
}

Matrix4& CQTransform::calWorldToLcalMatLH()
{
	Vector3 front = normalize(target_ - worldPos_);
	toLocalMat_[0][0] = right_.x;
	toLocalMat_[1][0] = right_.y;
	toLocalMat_[2][0] = right_.z;
	toLocalMat_[0][1] = up_.x;
	toLocalMat_[1][1] = up_.y;
	toLocalMat_[2][1] = up_.z;
	toLocalMat_[0][2] = front.x;
	toLocalMat_[1][2] = front.y;
	toLocalMat_[2][2] = front.z;
	toLocalMat_[3][0] = -dot(right_, worldPos_);
	toLocalMat_[3][1] = -dot(up_, worldPos_);
	toLocalMat_[3][2] = -dot(front, worldPos_);
	return toLocalMat_;
}

void CQTransform::__updateModelMat()
{
	auto scaleMat = getScaleMat();
	auto rotMat = getRotMat();
	auto transMat = getTranslateMat();

	srtMat_ = transMat * rotMat * transMat;
}

void CQTransform::__updateAxis()
{	
	up_ = up_* getRotMat();
	right_ = right_ * getRotMat();
	front_ = front_ * getRotMat();
}

void CQTransform::__setTransform(const CQTransform & other)
{
	this->parent_ = other.parent_;
	this->srtMat_ = other.srtMat_;
	this->rotQuatr_ = other.rotQuatr_;
	this->scale_ = other.scale_;
	this->relativePos_ = other.relativePos_;
	this->worldPos_ = other.worldPos_;
	this->up_ = other.up_;
	this->right_ = other.right_;
	this->front_ = other.front_;
	this->target_ = other.target_;
	this->toLocalMat_ = other.toLocalMat_;
}
