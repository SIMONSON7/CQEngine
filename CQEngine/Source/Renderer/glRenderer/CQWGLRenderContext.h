//*****************************************************************************
//
//! \file CQWGLRenderContext.h
//! \brief The encapsulation of wglext.
//! \author qiu_hao
//! \date 2019/10/31 11:45.pm
//
//*****************************************************************************
#ifndef __CQWGLRENDERCONTEXT_H__
#define __CQWGLRENDERCONTEXT_H__

// glad : <gl/GL.h> <gl/GLU.h> already included
#include <glad/glad.h> 
#include <wgl/wglext.h>
#include "CQBaseRenderContext.h"

#pragma comment(lib,"opengl32.lib")

NS_CQ_BEGIN

class CQWGLRenderContext : implements CQBaseRenderContext
{
public:
	CQWGLRenderContext(CQFrameConfiguration & config) : CQBaseRenderContext(config) {}
	virtual ~CQWGLRenderContext() {};
public:
	virtual void initContext() {};
	virtual void destroyContext() {};
	virtual void swapFrameBuff() {};
};

NS_CQ_END

#endif /*__CQWGLRENDERCONTEXT_H__*/
