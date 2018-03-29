#include "CQTimeStamp.h"

USING_NS_CQ

CQTimeStamp::CQTimeStamp()
{
	begin_ = high_resolution_clock::now();
}

void CQTimeStamp::tick()
{
	begin_ = high_resolution_clock::now();
}

double CQTimeStamp::getElapsedSecond()
{
	return  getElapsedTimeInMicroSec() * 0.000001;
}

double CQTimeStamp::getElapsedTimeInMilliSec()
{
	return getElapsedTimeInMicroSec() * 0.001;
}

long long CQTimeStamp::getElapsedTimeInMicroSec()
{
	long long t = duration_cast<microseconds>(high_resolution_clock::now() - begin_).count();
	return t;
}


