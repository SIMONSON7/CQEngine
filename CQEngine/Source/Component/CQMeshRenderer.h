//*****************************************************************************
//
//! \file CQMeshRenderer.h
//! \brief 
//! \author qiu_hao
//! \date 2018/11/08 10:25.pm
//
//*****************************************************************************

#ifndef __CQMESHRENDERER_H__
#define __CQMESHRENDERER_H__

#include <vector>
#include "CQComponent.h"

NS_CQ_BEGIN

class CQMesh;
class CQLight;
class CQMaterial;

class CQMeshRenderer : public CQComponent
{
public:
	typedef unsigned int MeshVertexArrayHandle;

public:
	explicit CQMeshRenderer();

	virtual ~CQMeshRenderer();

	CQMeshRenderer(const CQMeshRenderer& other) = default;

	CQMeshRenderer& operator=(const CQMeshRenderer& other) = default;

public:
	void setup(CQMesh * _mesh, CQLight * _light, std::vector<CQMaterial*> _materials);

public:
	inline CQMesh * getMesh() const { return mesh_; }

	inline CQLight * getLight() const { return light_; }

	inline std::vector<CQMaterial*> & getMaterials() { return materials_; }

	inline std::vector<MeshVertexArrayHandle> & getSubMeshHandles() { return subMeshHandles_; }

private:
	CQMesh * mesh_;

	CQLight * light_;

	std::vector<CQMaterial*> materials_;

	// array of VAO
	std::vector<MeshVertexArrayHandle> subMeshHandles_; 

};

NS_CQ_END

#endif /* __CQMESHRENDERER_H__ */