/*
*
*		qiu_hao		2018/02/05		18:08.pm
*/
#ifndef __CQWINAPPLICATION_H__
#define __CQWINAPPLICATION_H__

#include <windows.h>
#include "CQApplication.h"

NS_CQ_BEGIN

class CQWinApp :public CQAppI
{
public:
	CQWinApp(const char *_title, int _xPos, int _yPos, int _width, int _height);

	virtual ~CQWinApp();

	//virtual bool Initialize();
public:
	virtual void Run();

	static LRESULT CALLBACK  WndProc(HWND _hWnd, UINT _nMsg, WPARAM _wParam, LPARAM _lParam);
private:
	void CreateWnd();

	void RegisterWnd();

	void DisplayWnd();

private:
	HINSTANCE hInstance_;
	HWND	  hWnd_;
	TCHAR*	  appName_;

	int		  winWidth_;
	int		  winHeight_;
};

NS_CQ_END

#endif /*__CQWINAPPLICATION_H__*/



