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

#include "CQMacros.h"
#include "CQComponent.h"

NS_CQ_BEGIN

class CQVertexBuffer;
class CQIndexBuffer;

class CQMesh /*: public CQComponent*/
{
public:
	explicit CQMesh();

	explicit CQMesh(CQVertexBuffer* _vb, CQIndexBuffer* _ib);

	CQMesh(const CQMesh & other);

	CQMesh& operator=(const CQMesh &other);

	virtual ~CQMesh();

//public:
//	virtual const std::string& getName() const { return "Mesh"; }
};

NS_CQ_END

#endif /* __CQMESH_H__ */

