//*****************************************************************************
//
//! \file CQMesh.h
//! \brief 
//! \author qiu_hao
//! \date 2018/12/04 10:13.pm
//
//*****************************************************************************
#ifndef __CQMESH_H__
#define __CQMESH_H__

#include <vector>
#include "CQMacros.h"
#include "CQResI.h"
#include "CQNoncopyable.h"
#include "CQMath.h"

NS_CQ_BEGIN

struct Vertex
{
	Vector3 pos_;
	Vector3 normal_;
	Vector3 color_;
	Vector2 uv_;
};

struct SubMesh
{
	std::vector<Vertex> vBuff_;
	std::vector<unsigned int> iBuff_;
};

class CQMesh : public CQResI, private CQNoncopyable
{
public:
	CQMesh();

	virtual ~CQMesh();

public:
	virtual ResID getResID() const { return resID_; }

	virtual CQResI::Type getResType() const { return CQResI::Type::MESH; }

	virtual void onLoadDiskRes(const std::string & _abPath);

	virtual void onDestory();

private:
	ResID resID_;

	std::vector<SubMesh*> sharedMesh_;
};

NS_CQ_END

#endif /* __CQMESH_H__ */