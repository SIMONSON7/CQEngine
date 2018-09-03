#include "CQCore.h"

CQCore::CQCore()
{
	time_ = CQ_NEW(CQTime);
	scheduler_ = CQ_NEW(CQScheduler);
}

CQCore::~CQCore()
{
	CQ_DELETE(time_, CQTime);
	CQ_DELETE(scheduler_, CQScheduler);
}

CQCore* CQCore::shareCore()
{
	static CQCore s_core;
	return &s_core;
}

CQTime* CQCore::shareCQTime()
{
	return time_;
}

CQScheduler* CQCore::shareCQScheduler()
{
	return scheduler_;
}

void CQCore::__update()
{
	time_->__update(time_->calDeltaRealSecond());
	scheduler_->__update(time_->getDeltaGameSceond());
}

