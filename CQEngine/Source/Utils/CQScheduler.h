/*
*
*		qiu_hao		2018/08/20		22:55.pm
*/
#ifndef __CQSCHEDULER_H__
#define __CQSCHEDULER_H__

#include <map>
#include "CQMacros.h"
#include "CQUtils.h"

NS_CQ_BEGIN

class CQScheduler
{
public:
	struct TimeActionCfg
	{
		float second_;
		bool isRepeat_;
	};

public:
	virtual ~CQScheduler();

public:
	static
	CQScheduler *shareScheduler();

private:
	explicit CQScheduler();

	// non-copyable
	CQScheduler(const CQScheduler &) = delete;

	CQScheduler& operator=(const CQScheduler &) = delete;

private:
	std::map<TimeActionCfg, Action> actionMap_;
};

NS_CQ_END

#endif /* __CQSCHEDULER_H__ */



