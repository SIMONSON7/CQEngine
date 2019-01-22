#include <memory>
#include "CQTransform.h"
#include "CQCamera.h"


USING_NS_CQ;

CQCamera::CQCamera()
	:
	type_(CQCamera::PROJECTION_TYPE::PERSPECTIVE)
{

}

CQCamera::~CQCamera()
{

}

void CQCamera::onInit()
{

}

void CQCamera::update()
{

}

void CQCamera::onDestory()
{

}

void CQCamera::setType(CQCamera::PROJECTION_TYPE _type)
{
	type_ = _type;
}

Matrix4& CQCamera::calPerspectiveMat(float _fovy, float _aspect, float _zNear, float _zFar)
{
	setType(CQCamera::PROJECTION_TYPE::PERSPECTIVE);
	projMat_ = perspective(_fovy, _aspect, _zNear, _zFar);
	return projMat_;
}

Matrix4& CQCamera::calOrthographicMat(float _left, float _right, float _bottom, float _top, float _zNear, float _zFar)
{
	setType(CQCamera::PROJECTION_TYPE::ORTHOGRAPHIC);
	projMat_ = ortho(_left, _right, _bottom, _top, _zNear, _zFar);
	return projMat_;
}

CQCamera::PROJECTION_TYPE CQCamera::getType() const
{
	return type_;
}