#include "CQScheduler.h"

USING_NS_CQ

CQScheduler::~CQScheduler()
{

}

CQScheduler::CQScheduler()
{

}

void CQScheduler::__update(float _dltGameTime)
{
	if (actionMap_.empty())
	{
		return;
	}

	for each (auto item in actionMap_)
	{
		TimeAction ta = item.second;

		if (ta.isExipred(_dltGameTime))
		{
			ta.action_.invoke();
		}
	}
}
