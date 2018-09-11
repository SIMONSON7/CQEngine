#include "CQCore.h"
#include "CQTime.h"
#include "CQScheduler.h"

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

void CQCore::updateTime()
{
	time_->__update(time_->calDeltaRealSecond());
}

void CQCore::updateScheduler()
{
	scheduler_->__update(time_->getGameTimeSinceStartUp());
}

