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

Interface CQPrefabI
{
public:
	CQPrefabI() = default;

	virtual ~CQPrefabI() {};

public:
	virtual void setupGeometry() = 0;

	virtual void setupSurface() = 0;
};

class CQObject;

class CQPrefab : implements CQPrefabI
{
public:
	CQPrefab();

	virtual ~CQPrefab();

public:
	inline CQObject * getSceneObject() { return obj_; }

private:
	void __createObj();

private:
	CQObject * obj_;

};

NS_CQ_END

#endif /* __CQPREFAB_H__ */