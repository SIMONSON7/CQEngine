#include "CQWinApplication.h"
#include "CQEngine.h"

USING_NS_CQ

//============================ GLOBAL ============================//
#define DEF_WIN_WIDTH 800
#define DEF_WIN_HEIGHT 600

bool g_isExit = false;

CQAppI *g_app = CQ_NEW(CQWinApp, "CQEngine", 0, 0, DEF_WIN_WIDTH, DEF_WIN_HEIGHT);

LRESULT CALLBACK msWndEvtProc(HWND _hWnd, UINT _nMsg, WPARAM _wParam, LPARAM _lParam)
{
	if (g_app == nullptr)
	{
		// It should Never be executed here!
		g_app = CQ_NEW(CQWinApp, "CQEngine", 0, 0, DEF_WIN_WIDTH, DEF_WIN_HEIGHT);
		g_app->init();
	}

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
			dbgPuts("[WM_LBUTTONDOWN]\n");

			int x = (int)(LOWORD(_lParam));
			int y = (int)(HIWORD(_lParam));
			auto dispatcher = CQCore::shareCore()->shareEvtDispatcher();
			dispatcher->onMousePressL(x, y);
		}
		break;
		case WM_LBUTTONUP:
		{
			dbgPuts("[WM_LBUTTONUP]\n");

			int x = (int)(LOWORD(_lParam));
			int y = (int)(HIWORD(_lParam));
			auto dispatcher = CQCore::shareCore()->shareEvtDispatcher();
			dispatcher->onMouseReleaseL(x, y);
		}
		break;
		case WM_LBUTTONDBLCLK:
		{

		}
		break;
		case WM_RBUTTONDOWN:
		{
			dbgPuts("[WM_RBUTTONDOWN]\n");

			int x = (int)(LOWORD(_lParam));
			int y = (int)(HIWORD(_lParam));
			auto dispatcher = CQCore::shareCore()->shareEvtDispatcher();
			dispatcher->onMousePressR(x, y);
		}
		break;
		case WM_RBUTTONUP:
		{
			dbgPuts("[WM_RBUTTONUP]\n");

			int x = (int)(LOWORD(_lParam));
			int y = (int)(HIWORD(_lParam));
			auto dispatcher = CQCore::shareCore()->shareEvtDispatcher();
			dispatcher->onMouseReleaseR(x, y);
		}
		break;
		case WM_MOUSEMOVE:
		{

		}
		break;
		case WM_MOUSEWHEEL:
		{
			dbgPuts("[WM_MOUSEWHEEL]\n");

			int x = (int)(LOWORD(_lParam));
			int y = (int)(HIWORD(_lParam));
			int delta = GET_WHEEL_DELTA_WPARAM(_wParam);
			auto dispatcher = CQCore::shareCore()->shareEvtDispatcher();
			dispatcher->onMouseWheel(x, y, delta);
		}
		break;
		case WM_CHAR:
		{

		}
		break;
		case WM_KEYDOWN:
		{

		}
		break;
		case WM_SIZE:
		{
			int w = (int)(LOWORD(_lParam));
			int h = (int)(HIWORD(_lParam));
			CQCore::shareCore()->shareCQRender()->resize(w, h);
		}
		break;
		case WM_DESTROY:
		{
			g_isExit = true;
			PostQuitMessage(0);
		}
		break;
	}
	return DefWindowProc(_hWnd, _nMsg,
		_wParam, _lParam);
}
//============================ GLOBAL ============================//

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
	destroy();
}

void CQWinApp::init()
{
	__createWnd();
	CQCore::shareCore()->shareCQRender()->init(hWnd_);
}

void CQWinApp::tick()
{

}

void CQWinApp::destroy()
{
	__destroyWnd();
}

void CQWinApp::run()
{
	init();

	// Initialization the start scene.
	auto sm = CQSceneManager::shareSceneManager();
	auto cur = sm->registerStartScene();
	if (!cur)
	{
		dbgPuts("[ERROR] You app must config at least one scene!");
		return;
	}
	cur->onInit();

	MSG msg = {};
	
	CQTime *time = CQCore::shareCore()->shareCQTime();
	time->setTimeScale(1.0f);
	while (!g_isExit)
	{
		CQCore::shareCore()->updateTime();
		if (!time->isPause() && time->getDeltaGameSceond() > 1 / 60.0f)
		{
			// time.
			time->tick();
			CQCore::shareCore()->updateScheduler();

			// event.
			while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			// update.
			cur->update();

			// render.
			CQCore::shareCore()->shareCQRender()->update();
		}
		else
		{
			Sleep(1);
		}
	}

	sm->cleanAllScene();
	CQCore::shareCore()->shareCQRender()->destory();
	return;
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
	/*
	* CS_HREDRAW | CS_VREDRAW | CS_OWNDC
	* CS_HREDRAW : window's width change or coordinate x change.(WM_PAINT)
	* CS_VREDRAW : window's height change or coordinate y change.(WM_PAINT)
	* CS_OWNDC : for Pixel Format.
	*/
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = msWndEvtProc;
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

int CQWinApp::getWndWidth() const
{
	return winWidth_;
}

int CQWinApp::getWndHeight() const
{
	return winHeight_;
}

void CQWinApp::wndResize(int _width, int _height)
{
	winWidth_  = _width;
	winHeight_ = _height;
}

void CQWinApp::__destroyWnd()
{

}



