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
	void setLocalPos(const float3& _pos);

	void setRotEuler(const float3& _rot);

	void setRotQuart(const quaternion& _quart);

	void setScale(const float3& _scale);

	float3& getPos();

	float3& getRotEuler();

	quaternion& getRotQuart();

	float3& getScale();

private:
	float3 localPos_;
	float3 eulerRot_;
	float3 scale_;
	quaternion quatrRot_;
};

NS_CQ_END

#endif /* __CQTRANSFORM_H__ */