#include "CQWinApplication.h"

USING_NS_CQ

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
{}

void CQWinApp::Run()
{
	MSG msg = {};

	__createWnd();

	while (!isExit_)
	{
		while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return ;
}

void CQWinApp::__createWnd()
{
	hInstance_ = GetModuleHandle(NULL);
	WNDCLASSEX wc = {};

	WCHAR wszAppName[256];
	memset(wszAppName, 0, sizeof(wszAppName));
	MultiByteToWideChar(CP_ACP, 0, appName_, strlen(appName_) + 1, wszAppName,
		sizeof(wszAppName) / sizeof(wszAppName[0]));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
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

	ShowWindow(hWnd_, SW_SHOW);
	UpdateWindow(hWnd_);
}

LRESULT CALLBACK CQWinApp::WndProc(HWND _hWnd, UINT _nMsg, WPARAM _wParam, LPARAM _lParam)
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

///
CQAppI *g_app = CQ_RAW_NEW(CQWinApp,"CQEngine",0,0,800,600);

