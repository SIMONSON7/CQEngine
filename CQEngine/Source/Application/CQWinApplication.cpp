#include "CQWinApplication.h"
#include "CQMemory.h"

USING_NS_CQ

CQWinApp::CQWinApp(const char *_title, int _xPos, int _yPos, int _width, int _height)
{
	HINSTANCE hInstance_;
	HWND	  hWnd_;
	//appName_ = (title);
	winWidth_ = _width;
	winHeight_ = _height;
}

CQWinApp::~CQWinApp()
{

}

void CQWinApp::Run()
{
	CreateWnd();
	RegisterWnd();
	DisplayWnd();

}

void CQWinApp::CreateWnd()
{
	hInstance_ = (HINSTANCE)GetModuleHandle(NULL);
	hWnd_ = CreateWindowA(
		"",
		"",
		WS_OVERLAPPEDWINDOW  & ~WS_MAXIMIZEBOX ^ WS_THICKFRAME,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		winWidth_,
		winHeight_, NULL, NULL,
		hInstance_, NULL);
}

void CQWinApp::RegisterWnd()
{
	WNDCLASSEX wce = { 0 };
	wce.cbSize = sizeof(wce);
	wce.cbClsExtra = 0;
	wce.cbWndExtra = 0;
	wce.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wce.hCursor = NULL;
	wce.hIcon = LoadCursor(hInstance_, IDI_APPLICATION);
	wce.hIconSm = NULL;
	wce.hInstance = hInstance_;
	wce.lpfnWndProc = WndProc;
	wce.lpszClassName = "";
	wce.lpszMenuName = NULL;
	wce.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	ATOM nAtom = RegisterClassEx(&wce);
	if (0 == nAtom)
	{
		return;
	}
}

void CQWinApp::DisplayWnd()
{
	ShowWindow(hWnd_, SW_SHOW);
	UpdateWindow(hWnd_);
}

LRESULT CALLBACK CQWinApp::WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	switch (nMsg)
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
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, nMsg,
		wParam, lParam);
}

///
CQAppI *g_app = new CQWinApp("CQEngine",0,0,800,600);

