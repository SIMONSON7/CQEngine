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

class CQTransform : CQComponent
{
public:
	explicit CQTransform();

	virtual ~CQTransform();

	CQTransform(const CQTransform &);

	CQTransform& operator=(const CQTransform &);

public:
	virtual const std::string& getName() const;

public:
	void setLocalPos(const Vector3& _pos);

	void setRotEuler(const Vector3& _rot);

	void setRotQuart(const Quaternion& _quart);

	void setScale(const Vector3& _scale);

	Vector3& getPos();

	Vector3& getRotEuler();

	Quaternion& getRotQuart();

	Vector3& getScale();

	void lookAt(Vector3 _worldTarget, Vector3 _worldPos, Vector3 _worldUp);

	Matrix4& calWorldToLcalMatRH();

	Matrix4& calWorldToLcalMatLH();

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
};

NS_CQ_END

#endif /* __CQTRANSFORM_H__ */