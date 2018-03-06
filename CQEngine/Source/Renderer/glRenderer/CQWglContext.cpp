#include "CQWglContext.h"

USING_NS_CQ

PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;
PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

CQWglContext::CQWglContext()
	:
	hWnd_(NULL),
	hdc_(NULL),
	hglrc_(NULL)
{}

void CQWglContext::create()
{
	// error checks have been omitted for brevity
	// tmp render context //
	CQASSERT(hWnd_);
	hdc_ = GetDC(hWnd_);
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		8,				      // cAlphaBits
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	int pf = ChoosePixelFormat(hdc_, &pfd);
	SetPixelFormat(hdc_, pf, &pfd);

	HGLRC hglrc = wglCreateContext(hdc_);
	wglMakeCurrent(hdc_, hglrc);

	// init core context //
	wglGetExtensionsStringARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

	int32_t attrs[] =
	{
		WGL_SAMPLE_BUFFERS_ARB, 0,
		WGL_SAMPLES_ARB, 0,
		WGL_SUPPORT_OPENGL_ARB, true,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_DRAW_TO_WINDOW_ARB, true,
		WGL_DOUBLE_BUFFER_ARB, true,
		WGL_COLOR_BITS_ARB, 32,
		WGL_DEPTH_BITS_ARB, 24,
		WGL_STENCIL_BITS_ARB, 8,
		0
	};

	int pixelFormat;
	size_t  numFormats;
	wglChoosePixelFormatARB(hdc_, attrs, NULL, 1, &pixelFormat, &numFormats);
	SetPixelFormat(hdc_, pixelFormat, &pfd);

	GLint contextAttrs[9] = { WGL_CONTEXT_MAJOR_VERSION_ARB,  4,
		WGL_CONTEXT_MINOR_VERSION_ARB,  0,
		0, 0,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	hglrc_ = wglCreateContextAttribsARB(hdc_, 0, contextAttrs);

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hglrc);
	wglMakeCurrent(hdc_, hglrc_);

}

void  CQWglContext::destroy()
{
	if (hWnd_)
	{
		wglMakeCurrent(NULL, NULL);

		wglDeleteContext(hglrc_);
		hglrc_ = NULL;

		ReleaseDC(hWnd_, hdc_);
		hdc_ = NULL;
	}
}

void CQWglContext::swap()
{
	if (hdc_)
	{
		SwapBuffers(hdc_);
	}
}
