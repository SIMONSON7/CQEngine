//*****************************************************************************
//
//! \file CQCamera.h
//! \brief UVN Camera.
//! \author qiu_hao
//! \date 2018/09/16 11:03.pm
//
//*****************************************************************************

#ifndef __CQCAMERA_H__
#define __CQCAMERA_H__

#include <memory>
#include "CQMath.h"
#include "CQObject.h"

NS_CQ_BEGIN

class CQTransform;

class CQCamera : public CQObject
{
public:
	enum PROJECTION_TYPE
	{
		NONE,
		PERSPECTIVE,
		ORTHOGRAPHIC,
	};
public:
	explicit CQCamera();

	virtual ~CQCamera();

public:
	virtual void onInit();

	virtual void update();

	virtual void onDestory();

public:
	void setType(PROJECTION_TYPE _type);

	Matrix4& calPerspectiveMat(float _fovy, float _aspect, float _zNear, float _zFar);

	Matrix4& calOrthographicMat(float _left, float _right, float _bottom,float _top, float _zNear, float _zFar);

	std::shared_ptr<CQTransform> getTransform();

	PROJECTION_TYPE getType() const;

private:
	PROJECTION_TYPE type_;

	Matrix4 projMat_;
};

NS_CQ_END

#endif /* __CQCAMERA_H__ */

