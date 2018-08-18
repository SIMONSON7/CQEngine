#include <chrono>
#include "CQObject.h"

USING_NS_CQ

using std::chrono::system_clock;

CQObject::CQObject()
	:
	id_(genID())
{
	
}

const uint64_t CQObject::genID() const
{
	auto now = system_clock::now();
	auto now_c = system_clock::to_time_t(now);
	return now_c;
}