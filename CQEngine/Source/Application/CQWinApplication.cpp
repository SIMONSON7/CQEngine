#include "CQWinApplication.h"
#include "CQEngine.h"

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
	while (!isExit_)
	{
		CQCore::shareCore()->updateTime();
		if (!time->isPause() && time->getDeltaGameSceond() > 1 / 60.0f)
		{
			time->tick();
			CQCore::shareCore()->updateScheduler();

			cur->update();

			CQCore::shareCore()->shareCQRender()->update();

			while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
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
		{

		}
		break;
		case WM_MOUSEWHEEL:
		{

		}
		break;
		case WM_SIZE:
		{
			int width = (int)(LOWORD(_lParam));
			int height = (int)(HIWORD(_lParam));
			//////////// TMP ! ////////////
			/// NEED REFACTOR NOW! //////
			if (g_app != nullptr)
			{
				CQCore::shareCore()->shareCQRender()->resize(width, height);
			}
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
CQAppI *g_app = CQ_NEW(CQWinApp, "CQEngine", 0, 0, 800, 600);

