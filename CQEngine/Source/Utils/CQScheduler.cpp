#include "CQScheduler.h"

USING_NS_CQ

CQScheduler::~CQScheduler()
{

}

CQScheduler *CQScheduler::shareScheduler()
{
	static CQScheduler s_scheduler;
	return &s_scheduler;
}

CQScheduler::CQScheduler()
{

}
