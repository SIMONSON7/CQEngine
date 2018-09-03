/*
*
*		qiu_hao		2018/08/22		10:02.pm
*/
#ifndef __CQTIME_H__
#define __CQTIME_H__

#include "CQMacros.h"
#include <chrono>

NS_CQ_BEGIN

using namespace std::chrono;

class CQTime
{
public:
	virtual ~CQTime();

public:
	void pause(bool _v);

	bool isPause() const;

	void setTimeScale(float _scale);

	float getTimeScale() const;

	float getDeltaGameSceond() const;

	float getDeltaRealSecond() const;

	double getGameTimeSinceStartUp() const;

public:
	// You should NOT call the following interfaces individually!
	void tick();

	double calDeltaRealSecond();

	double calDeltaRealMilliSec();

	long long calDeltaRealMicroSec();

private:
	friend class CQCore;

	explicit CQTime();

	// non-copyable
	CQTime(const CQTime &) = delete;

	CQTime& operator=(const CQTime &) = delete;

	void __update(double _dtRealSecond);

private:
	bool isPause_;
	float scale_;
	double dtGameSecond_;
	/*long long*/double gameTimeSinceStartUp_;
	
	time_point<high_resolution_clock> begin_;
};

#include "CQTime.inl"

NS_CQ_END

#endif /* __CQTIME_H__ */