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
#include "CQObject.h"

NS_CQ_BEGIN

class CQCamera : CQObject
{
public:
	enum PROJECTION_TYPE
	{
		NONE,
		PERSPECTIVE,
		ORTHOGRAPHIC,
	};
//public:
//	explicit CQCamera();
//
//	virtual ~CQCamera();
//
//public:
//	virtual void onInit();
//
//	virtual void update();
//
//	virtual void onDestory();
//
//public:
//	std::shared_ptr<CQTransform> getTransform();

private:

};

NS_CQ_END

#endif /* __CQCAMERA_H__ */

