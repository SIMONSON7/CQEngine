#include <chrono>
#include "CQComponent.h"
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

void CQObject::setComponent(std::shared_ptr<CQComponent> _component)
{
	CQASSERT(_component);
	const std::string key = _component->getName();
	compMap_[key] = _component;
}

std::shared_ptr<CQComponent> CQObject::getComponentByName(const std::string& _name)
{
	return compMap_[_name];
}

void CQObject::removeComponent(const std::string& _name)
{
	compMap_.erase(_name);
}