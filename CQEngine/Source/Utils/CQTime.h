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
	explicit CQTime();

	virtual ~CQTime();

public:
	void pause(bool _v);

	bool isPause() const;

	void setTimeScale(float _scale);

	float getTimeScale() const;

	double getDeltaGameSceond() const;

	double getDeltaRealSecond() const;

	long long getGameTimeSinceStartUp() const;

public:
	// You should NOT call these interfaces individually!
	double getRealDeltaSecond();

	double getRealDeltaMilliSec();

	long long getRealDeltaMicroSec();

private:
#ifdef _MSC_VER
	friend class CQWinApp;
#endif
	void tick();

	void update(double _dtRealSecond);

private:
	bool isPause_;
	float scale_;
	double dtGameSecond_;
	long long gameTimeSinceStartUp_;
	
	time_point<high_resolution_clock> begin_;
};

#include "CQTime.inl"

NS_CQ_END

#endif /* __CQTIME_H__ */