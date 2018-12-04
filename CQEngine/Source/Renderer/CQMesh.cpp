#include "CQBuffer.h"
#include "CQMesh.h"

USING_NS_CQ

CQMesh::CQMesh()
{

}

CQMesh::CQMesh(CQVertexBuffer* _vb, CQIndexBuffer* _ib)
{

}

CQMesh::CQMesh(const CQMesh & other)
{

}

CQMesh& CQMesh::operator=(const CQMesh &other)
{
	return *this;
}

CQMesh::~CQMesh()
{

}

std::string CQMesh::getName() const
{
	return "Mesh";
}