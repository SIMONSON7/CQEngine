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
	void setLocalPos(const Vector3& _pos);

	void setRotEuler(const Vector3& _rot);

	void setRotQuart(const Quaternion& _quart);

	void setScale(const Vector3& _scale);

public:
	inline Vector3& getLocalPos() { return localPos_; }

	inline Vector3& getWorldPos() { return worldPos_; }

	inline Vector3& getRotEuler() { return eulerRot_; }

	inline Quaternion& getRotQuart() { return quatrRot_; }

	inline Vector3& getScale() { return scale_; }

public:
	Vector3& getFront();

	Vector3& getUp();

	Matrix4& calWorldToLcalMatRH();

	Matrix4& calWorldToLcalMatLH();

	// Build local right hand coordinate system.
	void lookAt(Vector3 _worldPos, Vector3 _worldTargetPos, Vector3 _worldUp);
//public:
//	Matrix4& scaleX(const float _scale);
//
//	Matrix4& scaleY(const float _scale);
//
//	Matrix4& scaleZ(const float _scale);
//
//	Matrix4& scale(const Vector3& _scale);
//
//public:
//	Matrix4& moveToX(const float _dist);
//
//	Matrix4& moveToY(const float _dist);
//
//	Matrix4& moveToZ(const float _dist);
//
//public:
//	Matrix4& rotateX(const float _angle);
//
//	Matrix4& rotateY(const float _angle);
//
//	Matrix4& rotateZ(const float _angle);

private:
	void __setTransform(const CQTransform & other);

	void __setWorldPos(const Vector3& _pos);

private:
	Vector3 scale_;
	Vector3 localPos_;
	Vector3 worldPos_;
	Vector3 eulerRot_;
	Quaternion quatrRot_;

	// Local coordinate system.
	Vector3 up_;
	Vector3 right_;
	Vector3 front_;
	Vector3 target_;/* FRONT = POS - TARGET */

	Matrix4 toLocalMat_;
};

NS_CQ_END

#endif /* __CQTRANSFORM_H__ */