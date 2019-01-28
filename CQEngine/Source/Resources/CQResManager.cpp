#include "CQResManager.h"
#include "rapidjson/document.h"

USING_NS_CQ

CQResManager::CQResManager()
{

}

CQResManager::~CQResManager()
{

}

CQResManager::SpCQResI CQResManager::getRes(const ResID _resID)
{
	return nullptr;
}

CQResManager::SpCQResI CQResManager::getRes(const std::string & _path)
{
	return nullptr;
}

bool CQResManager::destroyRes(const ResID _resID)
{
	return false;
}

bool CQResManager::destroyRes(const std::string & _path)
{
	return false;
}

