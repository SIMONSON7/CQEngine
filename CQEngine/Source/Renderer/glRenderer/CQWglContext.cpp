#include <string>
#include "CQWglContext.h"
#include "CQDebug.h"

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
{

}

CQWglContext::~CQWglContext()
{

}

void CQWglContext::initRenderContext()
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
	UINT  numFormats;
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

	// load glad.
	if (!gladLoadGL()) {
		exit(-1);
	}

}

void  CQWglContext::destroyRenderContext()
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

void CQWglContext::swapFrameBuff()
{
	if (hdc_)
	{
		SwapBuffers(hdc_);
	}
}

void CQWglContext::resizeView(int _width, int _height)
{
	if (hdc_)
	{
		glViewport(0, 0, (GLsizei)_width, _height);
	}
}

void CQWglContext::printRenderInfo()
{
	// OpenGL info
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION);
	dbgPrintf("[CQWglContext] OpenGL version : %s\n", OpenGLVersion);

	// profile. 
	// CQEngine only support Core profile.
	GLint mask;
	std::string profileName;
	glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &mask);
	if (mask & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT)
		profileName = "PROFILE_COMPATIBILITY";
	if (mask & GL_CONTEXT_CORE_PROFILE_BIT)
		profileName = "PROFILE_CORE";
	dbgPrintf("[CQWglContext] OpenGL profile : %s\n", profileName.c_str());

	// vendor
	dbgPrintf("[CQWglContext] OpenGL vendor : %s\n", glGetString(GL_VENDOR));

	// renderer
	dbgPrintf("[CQWglContext] OpenGL renderer : %s\n", glGetString(GL_RENDERER));

	// frame buffer
	GLint redbits, greenbits, bluebits, alphabits, depthbits, stencilbits;
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
		GL_BACK_LEFT,
		GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE,
		&redbits);
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
		GL_BACK_LEFT,
		GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE,
		&greenbits);
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
		GL_BACK_LEFT,
		GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE,
		&bluebits);
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
		GL_BACK_LEFT,
		GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE,
		&alphabits);
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
		GL_DEPTH,
		GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE,
		&depthbits);
	glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER,
		GL_STENCIL,
		GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE,
		&stencilbits);

	dbgPrintf("[CQWglContext] red : %u green : %u blue : %u alpha : %u depth : %u stencil : %u\n",
		redbits, greenbits, bluebits, alphabits, depthbits, stencilbits);

	// Accumulation Buffer(COMPATIBILITY) 
	//GLint accumredbits, accumgreenbits, accumbluebits, accumalphabits;
	//GLint auxbuffers;

	//glGetIntegerv(GL_ACCUM_RED_BITS, &accumredbits);
	//glGetIntegerv(GL_ACCUM_GREEN_BITS, &accumgreenbits);
	//glGetIntegerv(GL_ACCUM_BLUE_BITS, &accumbluebits);
	//glGetIntegerv(GL_ACCUM_ALPHA_BITS, &accumalphabits);
	//glGetIntegerv(GL_AUX_BUFFERS, &auxbuffers);

	//dbgPrintf(" accum red: %u accum green: %u accum blue: %u accum alpha: %u aux buffers: %u\n",
	//	accumredbits, accumgreenbits, accumbluebits, accumalphabits, auxbuffers);
}

void CQWglContext::setWndContext(HWND _hWnd)
{
	hWnd_ = _hWnd;
}