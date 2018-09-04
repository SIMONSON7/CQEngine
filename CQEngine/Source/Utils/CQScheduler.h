/*
*
*		qiu_hao		2018/08/20		22:55.pm
*/
#ifndef __CQSCHEDULER_H__
#define __CQSCHEDULER_H__

#include <map>
#include <memory>
#include "CQAction.h"
#include "CQMacros.h"
#include "CQMemory.h"

NS_CQ_BEGIN

class TimeAction
{
public:
	TimeAction()
		:
		action_(nullptr),
		isRepeat_(false),
		delaySecond_(0.0f),
		expiredSecond_(0.0f)
	{}

	TimeAction(const float _gameTime, Action *_action, const float _delaySecond, const bool _isRepeat)
	{
		CQASSERT(_action);
		action_ = _action;

		isRepeat_ = _isRepeat;
		delaySecond_ = _delaySecond;

		expiredSecond_ = 0.0f;
		expiredSecond_ += (_gameTime + delaySecond_);
	}

	~TimeAction() 
	{
		CQ_RAW_DELETE(action_);
	}

public:
	bool invoke()
	{
		bool isEnd = true;

		action_->invoke();
		if (isRepeat_)
		{
			expiredSecond_ += delaySecond_;
			isEnd = false;
		}

		return isEnd;
	}

	bool isExipred(float _gameTime)
	{
		return _gameTime >= expiredSecond_;
	}

private:
	Action *action_;

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
		 Action *_ac, const float _sec, const bool _isRepeat = false);

	void unregisterTimeAction(const int64_t _id);

private:
	friend class CQCore;

	explicit CQScheduler();

	// non-copyable
	CQScheduler(const CQScheduler &) = delete;

	CQScheduler& operator=(const CQScheduler &) = delete;

	void __update(float _gameTime);

	static int64_t __genID();

private:
	std::map<int64_t, std::shared_ptr<TimeAction>> actionMap_;
};

NS_CQ_END

#endif /* __CQSCHEDULER_H__ */



