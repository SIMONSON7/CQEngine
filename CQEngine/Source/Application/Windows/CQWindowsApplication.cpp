#include "CQWindowsApplication.h"

USING_NS_CQ

LRESULT CALLBACK CQWindowsApplication::msWndEvtProc(HWND _hWnd, UINT _nMsg, WPARAM _wParam, LPARAM _lParam)
{
	//if (g_pApp == nullptr)
	//{
	//	// It should Never be executed here!
	//	g_pApp = CQ_NEW(CQWinApp, "CQEngine", 0, 0, DEF_WIN_WIDTH, DEF_WIN_HEIGHT);
	//	g_pApp->init();
	//}

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
		//dbgPuts("[WM_LBUTTONDOWN]\n");

		//CQEvtDispatcher* dispatcher = CQCore::shareCore()->shareEvtDispatcher();
		//CQInput::MouseEvt* me = CQ_RAW_NEW(CQInput::MouseEvt);
		//me->id_ = CQInput::EvtID::MOUSE_L_CLICK_BEGIN;
		//me->x_ = (int)(LOWORD(_lParam));
		//me->y_ = (int)(HIWORD(_lParam));
		//dispatcher->notify(me);
		//CQ_RAW_DELETE(me);
	}
	break;
	case WM_LBUTTONUP:
	{
		//dbgPuts("[WM_LBUTTONUP]\n");

		//CQEvtDispatcher* dispatcher = CQCore::shareCore()->shareEvtDispatcher();
		//CQInput::MouseEvt* me = CQ_RAW_NEW(CQInput::MouseEvt);
		//me->id_ = CQInput::EvtID::MOUSE_L_CLICK_END;
		//me->x_ = (int)(LOWORD(_lParam));
		//me->y_ = (int)(HIWORD(_lParam));
		//dispatcher->notify(me);
		//CQ_RAW_DELETE(me);
	}
	break;
	case WM_LBUTTONDBLCLK:
	{

	}
	break;
	case WM_RBUTTONDOWN:
	{
		//dbgPuts("[WM_RBUTTONDOWN]\n");

		//CQEvtDispatcher* dispatcher = CQCore::shareCore()->shareEvtDispatcher();
		//CQInput::MouseEvt* me = CQ_RAW_NEW(CQInput::MouseEvt);
		//me->id_ = CQInput::EvtID::MOUSE_R_CLICK_BEGIN;
		//me->x_ = (int)(LOWORD(_lParam));
		//me->y_ = (int)(HIWORD(_lParam));
		//dispatcher->notify(me);
		//CQ_RAW_DELETE(me);
	}
	break;
	case WM_RBUTTONUP:
	{
		//CQEvtDispatcher* dispatcher = CQCore::shareCore()->shareEvtDispatcher();
		//CQInput::MouseEvt* me = CQ_RAW_NEW(CQInput::MouseEvt);
		//me->id_ = CQInput::EvtID::MOUSE_R_CLICK_END;
		//me->x_ = (int)(LOWORD(_lParam));
		//me->y_ = (int)(HIWORD(_lParam));
		//dispatcher->notify(me);
		//CQ_RAW_DELETE(me);
	}
	break;
	case WM_MOUSEMOVE:
	{

	}
	break;
	case WM_MOUSEWHEEL:
	{
		//dbgPuts("[WM_MOUSEWHEEL]\n");

		//CQEvtDispatcher* dispatcher = CQCore::shareCore()->shareEvtDispatcher();
		//CQInput::MouseEvt* me = CQ_RAW_NEW(CQInput::MouseEvt);
		//me->id_ = CQInput::EvtID::MOUSE_WHEEL;
		//me->x_ = (int)(LOWORD(_lParam));
		//me->y_ = (int)(HIWORD(_lParam));
		//me->delta_ = GET_WHEEL_DELTA_WPARAM(_wParam);
		//dispatcher->notify(me);
		//CQ_RAW_DELETE(me);
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
	case WM_KEYUP:
	{

	}
	break;
	case WM_SIZE:
	{
		//int w = (int)(LOWORD(_lParam));
		//int h = (int)(HIWORD(_lParam));
		//auto context = static_cast<CQWglContext*>(CQCore::shareCore()->shareCQRender()->getContext());
		//CQASSERT(context);
		//context->resizeView(w, h);
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		isQuit_ = true;
	}
	break;
	}

	return DefWindowProc(_hWnd, _nMsg,
		_wParam, _lParam);
}

CQWindowsApplication::CQWindowsApplication(const char * _appName, CQBaseRenderContext * _context)
	:
	CQApplicationBase(_appName, _context)
{

}

void CQWindowsApplication::initialize()
{
	CQApplicationBase::initialize();

	createWnd(appName_);
}

void CQWindowsApplication::finalize()
{
	CQApplicationBase::finalize();
}

void CQWindowsApplication::tick()
{
	CQApplicationBase::tick();

	MSG msg = {};

	// event.
	while (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}

void CQWindowsApplication::createWnd(const char * _wndName)
{
	CQASSERT(renderContext_);

	int width = renderContext_->getFrameConfiguration().screenWidth;
	int height = renderContext_->getFrameConfiguration().screenHeight;

	hInstance_ = GetModuleHandle(NULL);
	WNDCLASSEX wc = {};

	WCHAR wszAppName[256];
	memset(wszAppName, 0, sizeof(wszAppName));
	MultiByteToWideChar(CP_ACP, 0, _wndName, strlen(_wndName) + 1, wszAppName,
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
		width,
		height,
		NULL,
		NULL,
		hInstance_,
		NULL);

	ShowWindow(hWnd_, SW_SHOW);
	UpdateWindow(hWnd_);
}

