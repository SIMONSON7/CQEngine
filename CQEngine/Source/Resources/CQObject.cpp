#include <chrono>
#include "CQObject.h"

USING_NS_CQ

using std::chrono::system_clock;

CQObject::CQObject()
	:
	id_(getID())
{
	
}

void CQObject::setName(const std::string _name)
{
	name_ = _name;
}
const std::string& CQObject::getName() const
{
	return name_;
}

const uint32_t CQObject::getTag() const
{
	return tag_;
}
void CQObject::setTag(uint32_t _tag)
{
	tag_ = _tag;
}

const uint64_t CQObject::getID() const
{
	auto now = system_clock::now();
	auto now_c = system_clock::to_time_t(now);
	return now_c;
}