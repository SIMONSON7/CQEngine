//*****************************************************************************
//
//! \file CQPrefabFactory.h
//! \brief 
//! \author qiu_hao
//! \date 2019/04/12 06:11.pm
//
//*****************************************************************************
#ifndef __CQPREFABFACTORY_H__
#define __CQPREFABFACTORY_H__

#include "CQMacros.h"
#include "CQNoncopyable.h"

NS_CQ_BEGIN

class CQPrefab;

class CQPrefabFactory : private CQNoncopyable
{
public:
	static
	CQPrefab * createPlane(float _xsize, float _zsize, int _xdivs, int _zdivs, float _smax = 1.0F, float _tmax = 1.0F);

	static
	CQPrefab * createCube(float _side);

	static
	CQPrefab * createSphere();

private:
	CQPrefabFactory() = default;

	~CQPrefabFactory() = default;
};

NS_CQ_END

#endif /* __CQPREFABFACTORY_H__ */