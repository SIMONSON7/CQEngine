#include "CQApplicationBase.h"

USING_NS_CQ

CQApplicationBase::CQApplicationBase(CQIRenderContext * _context)
	:
	renderContext_(_context)
{

}

void CQApplicationBase::initialize()
{
	isQuit_ = false;
}

void CQApplicationBase::finalize()
{

}

void CQApplicationBase::tick()
{

}

bool CQApplicationBase::isQuit() { return isQuit_; }