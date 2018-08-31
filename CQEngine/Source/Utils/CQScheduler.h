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

struct TimeAction
{
	bool isRepeat_;
	float delaySecond_;
	long long expiredSecond_;
	Action action_;

	void init(double _gameTime, float _delaySecond, Action _action)
	{
		expiredSecond_ += (_gameTime + _delaySecond);
		action_ = _action;
	}

	bool isExipred(double _gameTime)
	{
		return expiredSecond_ >= _gameTime;
	}
};

class CQScheduler
{
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
	std::map<int64_t, Action> actionMap_;
};

NS_CQ_END

#endif /* __CQSCHEDULER_H__ */



