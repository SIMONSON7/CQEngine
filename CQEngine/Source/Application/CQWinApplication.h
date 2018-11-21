/*
*
*		qiu_hao		2018/02/05		18:08.pm
*/
#ifndef __CQWINAPPLICATION_H__
#define __CQWINAPPLICATION_H__

/*
* avoid Visual Studio settings :
* project-> Properties-> Configuration Properties-> General-> Character Set;
* default Unicode.
*/
#define UNICODE 
#include <windows.h>
// NO console window
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
#include "CQApplication.h"

NS_CQ_BEGIN

class CQWinApp : public CQAppI
{
public:
	CQWinApp(const char *_title, int _xPos, int _yPos, int _width, int _height);

	virtual ~CQWinApp();

public:
	virtual void run();

	virtual void init();

	virtual void tick();

	virtual void destroy();

public:
	int getWndWidth() const;

	int getWndHeight() const;

	void wndResize(int _width, int _height);

public:
	static LRESULT CALLBACK  wndProc(HWND _hWnd, UINT _nMsg, WPARAM _wParam, LPARAM _lParam);

private:
	void __createWnd();

	void __destroyWnd();

private:
	HINSTANCE hInstance_;
	HWND hWnd_;
	int winWidth_;
	int	winHeight_;
	const char *appName_;

	static bool isExit_;
};

NS_CQ_END

#endif /*__CQWINAPPLICATION_H__*/



