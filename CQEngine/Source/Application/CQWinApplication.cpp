#include "CQWinApplication.h"
#include "CQWglRenderer.h"
#include "CQDebug.h"

USING_NS_CQ

/////////////////////// TMP //////////////////
PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB;
PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

// test render
//PFNGLGENBUFFERSPROC glGenBuffers;
//PFNGLBINDBUFFERPROC glBindBuffer;
//PFNGLBUFFERDATAPROC glBufferData;
//PFNGLCREATESHADERPROC glCreateShader;
//PFNGLSHADERSOURCEPROC glShaderSource;
//PFNGLCOMPILESHADERPROC glCompileShader;
//PFNGLCREATEPROGRAMPROC glCreateProgram;


/////////////////////// TMP //////////////////

bool CQWinApp::isExit_ = false;

CQWinApp::CQWinApp(const char *_title, int _xPos, int _yPos, int _width, int _height)
	:
	appName_(_title),
	winWidth_(_width),
	winHeight_(_height),
	hInstance_(0),
	hWnd_(0)
{}

CQWinApp::~CQWinApp()
{
	puts("release CQWinApp");
	__destroyWnd();
}

void CQWinApp::run()
{
	MSG msg = {};

	__createWnd();

	/////////////////////// TMP //////////////////
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	// This will identify our vertex buffer
	GLuint vertexbuffer;

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	/////////////////////// TMP //////////////////

	while (!isExit_)
	{
		while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			/////////////////////// TMP //////////////////
			glClearColor(1.0f, 0.f, 0.f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);
			// Draw the triangle !
			glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
			glDisableVertexAttribArray(0);

			HDC hdc = GetDC(hWnd_);
			SwapBuffers(hdc);
			/////////////////////// TMP //////////////////
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return ;
}

void CQWinApp::__createWnd()
{
	/////////////////////// TMP //////////////////
	if (gladLoadGL()) {
		// you need an OpenGL context before loading glad
		printf("I did load GL with no context!\n");
		exit(-1);
	}
	/////////////////////// TMP //////////////////

	hInstance_ = GetModuleHandle(NULL);
	WNDCLASSEX wc = {};

	WCHAR wszAppName[256];
	memset(wszAppName, 0, sizeof(wszAppName));
	MultiByteToWideChar(CP_ACP, 0, appName_, strlen(appName_) + 1, wszAppName,
		sizeof(wszAppName) / sizeof(wszAppName[0]));

	wc.cbSize = sizeof(WNDCLASSEX);
	/*
	* CS_HREDRAW | CS_VREDRAW | CS_OWNDC
	* CS_HREDRAW : window's width change or coordinate x change.(WM_PAINT)
	* CS_VREDRAW : window's height change or coordinate y change.(WM_PAINT)
	* CS_OWNDC : for Pixel Format.
	*/
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = wndProc;
	wc.cbClsExtra = wc.cbWndExtra = NULL;
	wc.hInstance = hInstance_;
	wc.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = wszAppName;
	wc.hIcon = wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wc);

	hWnd_ = CreateWindowEx(NULL,
		wc.lpszClassName,
		wc.lpszClassName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		winWidth_,
		winHeight_,
		NULL,
		NULL,
		hInstance_,
		NULL);

	/////////////////////// TMP ////////////////// 
	// error checks have been omitted for brevity
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
	HDC hdc = GetDC(hWnd_);
	int  pf = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, pf, &pfd);
	HGLRC hglrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hglrc);

	// init core context
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
	wglChoosePixelFormatARB(hdc, attrs, NULL, 1, &pixelFormat, &numFormats);
	SetPixelFormat(hdc, pixelFormat, &pfd);

	GLint contextAttrs[9] = { WGL_CONTEXT_MAJOR_VERSION_ARB,  4,
						WGL_CONTEXT_MINOR_VERSION_ARB,  0,
						0, 0,
						WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
						0
					};

	HGLRC context = wglCreateContextAttribsARB(hdc, 0, contextAttrs);

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hglrc);
	wglMakeCurrent(hdc, context);

	// test render
	if (!gladLoadGL()) {
		printf("Something went wrong!\n");
		exit(-1);
	}

	const GLubyte* OpenGLVersion = glGetString(GL_VERSION);
	dbgPrintf("opengl version:%s",OpenGLVersion);
	
	/////////////////////////////////////////
	ShowWindow(hWnd_, SW_SHOW);
	UpdateWindow(hWnd_);
}

LRESULT CALLBACK CQWinApp::wndProc(HWND _hWnd, UINT _nMsg, WPARAM _wParam, LPARAM _lParam)
{
	switch (_nMsg)
	{
	case WM_CREATE:
	{


	}
	break;
	case WM_COMMAND:
	{

	}
	break;
	case WM_PAINT:
	{
		
	}
		break;
	case WM_LBUTTONDOWN:
	{
		
	}
	break;
	case WM_LBUTTONUP:
	{

	}
	break;
	case WM_RBUTTONDOWN:
	{

	}
	break;
	case WM_RBUTTONUP:
	{

	}
	break;
	case WM_MOUSEMOVE:
	{

	}
	break;
	case WM_LBUTTONDBLCLK:

		break;
	case WM_MOUSEWHEEL:
	{

	}
	break;
	case WM_DESTROY:
	{
		isExit_ = true;
		PostQuitMessage(0);
	}
		break;
	}
	return DefWindowProc(_hWnd, _nMsg,
		_wParam, _lParam);
}

void CQWinApp::__destroyWnd()
{

}

///
CQAppI *g_app = CQ_NEW(CQWinApp,"CQEngine",0,0,800,600);

