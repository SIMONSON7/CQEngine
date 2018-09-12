#include "CQCore.h"
#include "CQTime.h"
#include "CQScheduler.h"
#include "CQRenderer.h"

CQCore::CQCore()
{
	time_ = CQ_NEW(CQTime);
	scheduler_ = CQ_NEW(CQScheduler);
	render_ = CQ_NEW(CQRenderer);
}

CQCore::~CQCore()
{
	CQ_DELETE(time_, CQTime);
	CQ_DELETE(scheduler_, CQScheduler);
	CQ_DELETE(render_, CQRenderer);
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

CQRenderer* CQCore::shareCQRender()
{
	return render_;
}

void CQCore::updateTime()
{
	time_->__update(time_->calDeltaRealSecond());
}

void CQCore::updateScheduler()
{
	scheduler_->__update(time_->getGameTimeSinceStartUp());
}

