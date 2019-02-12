#include "CQCore.h"
#include "CQTime.h"
#include "CQScheduler.h"
#include "CQEvtDispatcher.h"
#include "CQResManager.h"
#include "CQCuller.h"
#include "CQRenderer.h"

USING_NS_CQ

CQCore::CQCore()
{
	time_ = CQ_NEW(CQTime);
	scheduler_ = CQ_NEW(CQScheduler);
	evtDispatcher_ = CQ_NEW(CQEvtDispatcher);
	resManager_ = CQ_NEW(CQResManager);
	culler_ = CQ_NEW(CQCuller);
	render_ = CQ_NEW(CQRenderer);
}

CQCore::~CQCore()
{
	CQ_DELETE(time_, CQTime);
	CQ_DELETE(scheduler_, CQScheduler);
	CQ_DELETE(evtDispatcher_, CQEvtDispatcher);
	CQ_DELETE(resManager_, CQResManager);
	CQ_DELETE(culler_, CQCuller);
	CQ_DELETE(render_, CQRenderer);
}

CQCore * CQCore::shareCore()
{
	static CQCore s_core;
	return &s_core;
}

CQTime * CQCore::shareCQTime()
{
	return time_;
}

CQScheduler * CQCore::shareCQScheduler()
{
	return scheduler_;
}

CQEvtDispatcher * CQCore::shareEvtDispatcher()
{
	 return evtDispatcher_;
}

CQResManager * CQCore::shareResManager()
{
	return resManager_;
}

CQCuller * CQCore::shareCuller()
{
	return culler_;
}

CQRenderer * CQCore::shareCQRender()
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

