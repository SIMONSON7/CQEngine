#include "CQRenderer.h"

USING_NS_CQ

CQRenderer::CQRenderer()
{
}

CQRenderer:: ~CQRenderer()
{
}

void CQRenderer::init(HWND _hWnd)
{
	__initDisplayCtx(_hWnd);
}

void CQRenderer::update()
{
	ctx_.swapBuff();
}

void CQRenderer::destory()
{
	ctx_.destroy();
}

void CQRenderer::__initDisplayCtx(HWND _hWnd)
{
	ctx_.hWnd_ = _hWnd;
	ctx_.init();
	ctx_.printRenderInfo();
}

