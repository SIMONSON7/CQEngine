#include <utility>
#include "CQResManager.h"
#include "CQIO.h"
#include "CQDebug.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

USING_NS_CQ

CQResManager::CQResManager()
{
	__parseResCfg();
}

CQResManager::~CQResManager()
{
	resMap_.clear();
	resLoadedMap_.clear();
	resDontDestroyMap_.clear();
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

void CQResManager::__parseResCfg()
{
	CQIO::addSearchPath(CQIO::getCurDir() + "/GIT_SOURCE" + "/CQEngine/CQEngine/Assets/config/");
	CQIO::addSearchPath(CQIO::getCurDir() + "/GIT_SOURCE" + "/CQEngine/CQEngine/Assets/img/");
	CQIO::addSearchPath(CQIO::getCurDir() + "/GIT_SOURCE" + "/CQEngine/CQEngine/Assets/shader/");
	CQIO::addSearchPath(CQIO::getCurDir() + "/GIT_SOURCE" + "/CQEngine/CQEngine/Assets/texture/");
	dbgPuts(CQIO::getCurDir().c_str());

	auto jsonData = CQIO::cvLoadFile("ResConf.json");
	if (jsonData->staus_ == Data::LOAD_SUCCESS)
	{
		using namespace rapidjson;
		{
			Document d;
			d.Parse(static_cast<char*>(jsonData->buff_));
			if (d.HasParseError())
			{
				dbgPuts("[CQResManager] parse ResConf.json wrong.");
				return;
			}

			using rapidjson::Value;
			{
				Value & res = d["Res"];
				if (res.IsArray())
				{	
					for (int i = 0 ; i < res.Size(); ++i)
					{
						Value & it = res[i];
						std::string name = it["name"].GetString();
						std::string url = it["url"].GetString();

						CQResConfig cfg(name, url);
						ResID id(i);
						resMap_.insert(std::make_pair(id, cfg));
					}
				}
			}
		}
	}
}

