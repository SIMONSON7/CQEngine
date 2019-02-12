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

#include <vector>
#include "CQNoncopyable.h"

NS_CQ_BEGIN

class CQContext;
class CQObject;
class CQRenderQueue;
class CQMeshRenderer;

class CQRenderer : private CQNoncopyable
{
public:
	virtual ~CQRenderer();

public:
	CQContext * getContext();

	void draw(std::vector<CQObject*> _visibleObjs);

private:
	void __drawNormal(CQMeshRenderer * _meshRender);

	void __drawTransparent(CQMeshRenderer * _meshRender);

private:
	friend class CQCore;

	explicit CQRenderer();

private:
	CQContext * context_;

	CQRenderQueue * renderQueue_;

};

NS_CQ_END

#endif /*__CQRENDERER_H__*/

