//*****************************************************************************
//
//! \file CQRenderer.h
//! \brief interface file of render.
//! \author qiu_hao
//! \date 2018/03/31 05:57.pm
//
//*****************************************************************************
#ifndef __CQRENDERER_H__
#define __CQRENDERER_H__

#include "CQMacros.h"
#if defined(_MSC_VER)
	#include "CQWglContext.h"
#endif

NS_CQ_BEGIN

class CQRenderer
{
public:
	virtual ~CQRenderer();

public:
#if defined(_MSC_VER)
	void init(HWND _hWnd);
#else
	void init();
#endif

	void update();

	void destory();

private:
	friend class CQCore;

	explicit CQRenderer();

	// non-copyable
	CQRenderer(const CQRenderer &) = delete;

	CQRenderer& operator=(const CQRenderer &) = delete;

// rendering pipeline
private:
	void __initDisplayCtx(HWND _hWnd);

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

private:
#if defined(_MSC_VER)
	CQWglContext ctx_;
#endif
};

NS_CQ_END

#endif /*__CQRENDERER_H__*/

