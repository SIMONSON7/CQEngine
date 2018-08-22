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

void CQTime::update(double _dtRealSecond)
{
	if (!isPause_)
	{
		dtGameSecond_ = _dtRealSecond * scale_;
		gameTimeSinceStartUp_ += dtGameSecond_;
	}
}

void CQTime::tick()
{
	begin_ = high_resolution_clock::now();
}

double CQTime::getRealDeltaSecond()
{
	return  getRealDeltaMicroSec() * 0.000001;
}

double CQTime::getRealDeltaMilliSec()
{
	return getRealDeltaMicroSec() * 0.001;
}

long long CQTime::getRealDeltaMicroSec()
{
	long long t = duration_cast<microseconds>(high_resolution_clock::now() - begin_).count();
	return t;
}

