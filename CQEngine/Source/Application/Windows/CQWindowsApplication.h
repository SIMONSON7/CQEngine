//*****************************************************************************
//
//! \file CQWindowsApplication.h
//! \brief The application of Windows.
//! \author qiu_hao
//! \date 2019/10/29 11:09.pm
//
//*****************************************************************************
#ifndef __CQ_WINDOWSAPPLICATION_H__
#define __CQ_WINDOWSAPPLICATION_H__

/*
* avoid Visual Studio settings :
* project-> Properties-> Configuration Properties-> General-> Character Set;
* default Unicode.
*/
#define UNICODE 
#include <windows.h>
// NO console window
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
#include "CQApplicationBase.h"

NS_CQ_BEGIN

class CQWindowsApplication : public CQApplicationBase
{
public:
	CQWindowsApplication(const char * _appName, CQBaseRenderContext * _context);
	virtual ~CQWindowsApplication() {};

public:
	virtual void initialize();
	virtual void tick();
	virtual void finalize();

protected:
	void createWnd(const char * _wndName);

private:
	static LRESULT CALLBACK msWndEvtProc(HWND _hWnd,
		UINT _nMsg, WPARAM _wParam, LPARAM _lParam);

protected:
	HWND hWnd_;
	HINSTANCE hInstance_;
};

NS_CQ_END

#endif /*__CQ_WINDOWSAPPLICATION_H__*/



