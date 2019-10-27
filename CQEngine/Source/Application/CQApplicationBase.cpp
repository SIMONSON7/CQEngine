#include "CQApplicationBase.h"

USING_NS_CQ

CQApplicationBase g_application;
CQIApplication * g_pApplication = &g_application;

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