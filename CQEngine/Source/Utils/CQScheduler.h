/*
*
*		qiu_hao		2018/08/20		22:55.pm
*/
#ifndef __CQSCHEDULER_H__
#define __CQSCHEDULER_H__

#include <map>
#include <memory>
#include "CQMacros.h"
#include "CQUtils.h"

NS_CQ_BEGIN

class TimeAction
{
public:
	TimeAction()
		:
		action_(),
		isRepeat_(false),
		delaySecond_(0.0f),
		expiredSecond_(0.0f)
	{}

	TimeAction(float _gameTime, Action _action, float _delaySecond, bool _isRepeat)
	{
		expiredSecond_ += (_gameTime + _delaySecond);
		action_ = _action;
	}

	~TimeAction() {}

public:
	bool invoke()
	{
		bool isEnd = true;

		action_.invoke();
		if (isRepeat_)
		{
			expiredSecond_ += delaySecond_;
			isEnd = false;
		}

		return isEnd;
	}

	bool isExipred(float _gameTime)
	{
		return expiredSecond_ >= _gameTime;
	}

private:
	Action action_;

	bool isRepeat_;
	float delaySecond_;
	double expiredSecond_;
};

class CQScheduler
{
public:
	virtual ~CQScheduler();

public:
	int64_t registerTimeAction(const float _gameTime, 
		const Action _ac, const float _sec, const bool _isRepeat = false);

	void unregisterTimeAction(const int64_t _id);

private:
	friend class CQCore;

	explicit CQScheduler();

	// non-copyable
	CQScheduler(const CQScheduler &) = delete;

	CQScheduler& operator=(const CQScheduler &) = delete;

	void __update(float _dltGameTime);

	static int64_t __genID();

private:
	std::map<int64_t, std::shared_ptr<TimeAction>> actionMap_;
};

NS_CQ_END

#endif /* __CQSCHEDULER_H__ */



