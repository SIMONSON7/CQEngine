#include "CQApplicationBase.h"

USING_NS_CQ

// define static member data.
bool CQApplicationBase::isQuit_ = false;

CQApplicationBase::CQApplicationBase(const char * _appName, CQBaseRenderContext * _context)
	:
	appName_(_appName),
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