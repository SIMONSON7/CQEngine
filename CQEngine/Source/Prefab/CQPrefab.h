//*****************************************************************************
//
//! \file CQPrefab.h
//! \brief 
//! \author qiu_hao
//! \date 2019/04/03 11:03.pm
//
//*****************************************************************************
#ifndef __CQPREFAB_H__
#define __CQPREFAB_H__

#include "CQMacros.h"
#include <vector>

NS_CQ_BEGIN

class CQMesh;
class CQLight;
class CQMaterial;
class CQSceneNode;

Interface CQPrefabI
{
public:
	CQPrefabI() = default;

	virtual ~CQPrefabI() {};

public:
	virtual void setupSurface(CQMaterial * _mat, CQLight * _light = nullptr) = 0;
};

class CQPrefab : implements CQPrefabI
{
public:
	CQPrefab();

	virtual ~CQPrefab();

public:
	virtual void setupSurface(CQMaterial * _mat, CQLight * _light = nullptr);

public:
	inline CQSceneNode * getSceneNode() { return node_; }

protected:
	CQSceneNode * node_;

};

NS_CQ_END

#endif /* __CQPREFAB_H__ */