//*****************************************************************************
//
//! \file CQTransform.h
//! \brief 
//! \author qiu_hao
//! \date 2018/11/08 10:25.pm
//
//*****************************************************************************

#ifndef __CQTRANSFORM_H__
#define __CQTRANSFORM_H__

#include "CQComponent.h"
#include "CQMath.h"

NS_CQ_BEGIN

class CQTransform : public CQComponent
{
public:
	explicit CQTransform();

	virtual ~CQTransform();

	CQTransform(const CQTransform& other);

	CQTransform& operator=(const CQTransform& other);

public:
	static const Vector3 sWorldUp;

	static const Vector3 sWorldRight;

	static const Vector3 sWorldFront;

	// Origin
	static const Vector3 sLocalPos;

// Scale :
public:
	void setScale(const Vector3& _scale);

	Matrix4 getScaleMat();

	inline Vector3& getScale() { return scale_; }

// Rotation
public:
	void rot(const float angle, const Vector3& axis);

	void rotateX(const float _angle);

	void rotateY(const float _angle);

	void rotateZ(const float _angle);

	inline Vector3 getRotEuler() { return eulerAngles(rotQuatr_); }

	inline Matrix4 getRotMat() { return mat4_cast(rotQuatr_); }

	inline Quaternion& getRotQuatr() { return rotQuatr_; }

// Translate
public:
	void move(Vector3& _worldPos);

	void moveTo(Vector3& _worldOffset);

	Matrix4 getTranslateMat();

	inline Vector3& getLocalPos() { return relativePos_; }

	inline Vector3& getWorldPos() { return worldPos_; }

// Coordinate transformation
public:
	// Build local right hand coordinate system.
	void buildLocalCoordinate(Vector3& _worldPos, Vector3& _worldTargetPos, Vector3& _worldUp);

	Matrix4& calWorldToLcalMatRH();

	Matrix4& calWorldToLcalMatLH();

	inline Vector3& getRight() { return right_; }

	inline Vector3& getFront() { return front_; }

	inline Vector3& getUp() { return up_; }

public:
	inline Matrix4& getModelMat() { return srtMat_; }

private:
	void __updateModelMat();

	void __updateAxis();

	void __setTransform(const CQTransform & other);

private:
	CQTransform *parent_;

	Matrix4 srtMat_;

	// Basic transform.
	Quaternion rotQuatr_;

	Vector3 scale_;

	Vector3 relativePos_;

	Vector3 worldPos_;

	// Local coordinate system.
	Vector3 up_;

	Vector3 right_;

	Vector3 front_;

	Vector3 target_;

	Matrix4 toLocalMat_;
};

NS_CQ_END

#endif /* __CQTRANSFORM_H__ */