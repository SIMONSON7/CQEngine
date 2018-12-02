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

	CQTransform(const CQTransform & other);

	CQTransform& operator=(const CQTransform &other);

public:
	virtual std::string getName() const;

public:
	// Build local right hand coordinate system.
	void lookAt(Vector3 _worldPos, Vector3 _targetPos, Vector3 _worldUp);

	void setLocalPos(const Vector3& _pos);

	void setWorldPos(const Vector3& _pos);

	void setRotEuler(const Vector3& _rot);

	void setRotQuart(const Quaternion& _quart);

	void setScale(const Vector3& _scale);

	Vector3& getLocalPos();

	Vector3& getWorldPos();

	Vector3& getRotEuler();

	Quaternion& getRotQuart();

	Vector3& getScale();

	Vector3& getFront();

	Vector3& getUp();

	Matrix4& calWorldToLcalMatRH();

	Matrix4& calWorldToLcalMatLH();

private:
	void __setTransform(const CQTransform & other);

private:
	Vector3 scale_;
	Vector3 localPos_;
	Vector3 worldPos_;
	Vector3 eulerRot_;
	Quaternion quatrRot_;

	// Local coordinate system.
	Vector3 up_;
	Vector3 right_;
	Vector3 target_;/* FRONT = POS - TARGET */

	Matrix4 toLocalMat_;
};

NS_CQ_END

#endif /* __CQTRANSFORM_H__ */