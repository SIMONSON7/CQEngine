/*
*
*		qiu_hao		2018/03/06		03:56.pm
*/
#ifndef __CQWGLCONTEXT_H__
#define __CQWGLCONTEXT_H__

// glad :
// <gl/GL.h> <gl/GLU.h> already included
#include <glad/glad.h> 
#include <wgl/wglext.h>
#include "CQMacros.h"

#pragma comment(lib,"opengl32.lib")

NS_CQ_BEGIN

struct CQWglContext
{
	CQWglContext();
	void create();
	void destroy();
	void update();
	void printGLInfo();
	//void makeCurrent();

	HWND hWnd_;
	HDC hdc_;
	HGLRC hglrc_;
};

NS_CQ_END

#endif /*__CQWGLCONTEXT_H__*/







