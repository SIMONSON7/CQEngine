//*****************************************************************************
//
//! \file CQWglContext.h
//! \brief The encapsulation of wglext.
//! \author qiu_hao
//! \date 2018/03/06 03:56.pm
//
//*****************************************************************************
#ifndef __CQWGLCONTEXT_H__
#define __CQWGLCONTEXT_H__

// glad : <gl/GL.h> <gl/GLU.h> already included
#include <glad/glad.h> 
#include <wgl/wglext.h>
#include "CQMacros.h"
#include "CQContext.h"

#pragma comment(lib,"opengl32.lib")

NS_CQ_BEGIN

class CQWglContext : public CQContext
{
public:
	CQWglContext();

	virtual ~CQWglContext();

public:
	virtual void initRenderContext();

	virtual void destroyRenderContext();

	virtual void swapFrameBuff();

	virtual void resizeView(int _width, int _height);

public:
	void setWndContext(HWND _hWnd);

	void printRenderInfo();

	//void makeCurrent();

private:
	HDC hdc_;
	HWND hWnd_;
	HGLRC hglrc_;
};

NS_CQ_END

#endif /*__CQWGLCONTEXT_H__*/







