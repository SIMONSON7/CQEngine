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
	ctx_.hWnd_ = _hWnd;
	ctx_.init();
	ctx_.printRenderInfo();
}

void CQRenderer::update()
{
	ctx_.update();
}

void CQRenderer::destory()
{
	ctx_.destroy();
}