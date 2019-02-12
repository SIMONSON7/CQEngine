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
	explicit CQMeshRenderer();

	virtual ~CQMeshRenderer();

	CQMeshRenderer(const CQMeshRenderer& other);

	CQMeshRenderer& operator=(const CQMeshRenderer& other);

public:



private:
	CQMesh * mesh_;

	CQLight * light_;

	std::vector<CQMaterial*> materials_;

};

NS_CQ_END

#endif /* __CQMESHRENDERER_H__ */