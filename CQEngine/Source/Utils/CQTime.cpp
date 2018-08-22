#include "CQTime.h"

USING_NS_CQ

CQTime::CQTime()
	:
	isPause_(false),
	scale_(1.0f),
	dtGameSecond_(0.0f),
	gameTimeSinceStartUp_(0)
{
	begin_ = high_resolution_clock::now();
}

CQTime::~CQTime()
{

}

void CQTime::tick()
{
	begin_ = high_resolution_clock::now();
}

double CQTime::calDeltaRealSecond()
{
	return  calDeltaRealMicroSec() * 0.000001;
}

double CQTime::calDeltaRealMilliSec()
{
	return calDeltaRealMicroSec() * 0.001;
}

long long CQTime::calDeltaRealMicroSec()
{
	long long t = duration_cast<microseconds>(high_resolution_clock::now() - begin_).count();
	return t;
}

void CQTime::__update(double _dtRealSecond)
{
	if (!isPause_)
	{
		dtGameSecond_ = _dtRealSecond * scale_;
		gameTimeSinceStartUp_ += dtGameSecond_;
	}
}

