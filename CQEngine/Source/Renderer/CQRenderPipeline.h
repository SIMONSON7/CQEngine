//*****************************************************************************
//
//! \file CQRenderPipeline.h
//! \brief The underlying rendering interface.
//! \author qiu_hao
//! \date 2018/10/06 22:47.pm
//
//*****************************************************************************
#ifndef __CQRENDERPIPELINE_H__
#define __CQRENDERPIPELINE_H__

#include "CQMacros.h"

class CQRenderPipeline 
{
public:
	~CQRenderPipeline();

	CQRenderPipeline();

	CQRenderPipeline(const CQRenderPipeline &);

	CQRenderPipeline& operator=(const CQRenderPipeline &);

public:
	

// Rendering pipeline.
private:
	// Geometry processing 

	void __vertexShading();

	void __opTessellation();

	void __opGeometryShading();

	void __projection();

	void __clipping();

	void __screenMapping();

	// Rasterization

	void __primitiveAssembly();

	void __triangleTraversal();

	// Pixel processing

	void __fragmentShading();

	void __merging();

} final;

#endif /* __CQRENDERPIPELINE_H__ */