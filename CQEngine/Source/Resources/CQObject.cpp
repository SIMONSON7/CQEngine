#include "CQObject.h"

USING_NS_CQ

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