#include <utility>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "CQResManager.h"
#include "CQIO.h"
#include "CQDebug.h"
#include "CQShader.h"
#include "CQTexture.h"
#include "CQMesh.h"

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

CQResManager::SpCQResI CQResManager::getRes(const std::string & _resName)
{
	if (_resName.empty())
	{
		dbgPuts("[CQResManager] getRes() : invalid resName.");
		return nullptr;
	}

	auto cfg = resMap_.find(_resName);
	if (cfg != resMap_.end())
	{
		auto loadedRes = resLoadedMap_.find(cfg->second.path_);
		if (loadedRes != resLoadedMap_.end())
		{
			return loadedRes->second;
		}

		auto nodestroyRes = resDontDestroyMap_.find(cfg->second.path_);
		if (nodestroyRes != resDontDestroyMap_.end())
		{
			return nodestroyRes->second;
		}

		std::shared_ptr<CQResI> baseResSP;
		switch (cfg->second.type_)
		{
		case ResType::SHADER:
		{
			std::shared_ptr<CQShader> shaderResSP = std::make_shared<CQShader>();
			shaderResSP->onLoadDiskRes(cfg->second.abPath_);
			baseResSP = std::dynamic_pointer_cast<CQResI>(shaderResSP);
		}
		break;
		case ResType::TEXTURE:
		{
			std::shared_ptr<CQTexture> texResSP = std::make_shared<CQTexture>();
			texResSP->onLoadDiskRes(cfg->second.abPath_);
			baseResSP = std::dynamic_pointer_cast<CQResI>(texResSP);
		}
		break;
		case ResType::MESH:
		{
			std::shared_ptr<CQMesh> meshRes = std::make_shared<CQMesh>();
			meshRes->onLoadDiskRes(cfg->second.abPath_);
			baseResSP = std::dynamic_pointer_cast<CQResI>(meshRes);
		}
		break;
		default:
			break;
		}
		resLoadedMap_.insert(std::make_pair(cfg->second.path_, baseResSP));
		return baseResSP;
	}

	return nullptr;
}

bool CQResManager::destroyRes(const std::string & _resName)
{
	if (_resName.empty())
	{
		dbgPuts("[CQResManager] getRes() : invalid resName.");
		return nullptr;
	}

	auto cfg = resMap_.find(_resName);
	SpCQResI res = nullptr;
	if (cfg != resMap_.end())
	{
		auto loadedRes = resLoadedMap_.find(cfg->second.path_);
		if (loadedRes != resLoadedMap_.end())
		{
			res = loadedRes->second;
		}

		auto nodestroyRes = resDontDestroyMap_.find(cfg->second.path_);
		if (nodestroyRes != resDontDestroyMap_.end())
		{
			res = loadedRes->second;
		}

		if (res != nullptr)
		{
			res->onDestory();
			return true;
		}
		return false;
	}

	return false;
}

void CQResManager::__parseResCfg()
{
	std::string assestsPath = CQIO::getCurDir() /*+ "/GIT_SOURCE" */+ "/CQEngine/CQEngine/Assets/";
	CQIO::addSearchPath(assestsPath + "config/");
	CQIO::addSearchPath(assestsPath + "img/");
	CQIO::addSearchPath(assestsPath + "shader/");
	CQIO::addSearchPath(assestsPath + "texture/");
	CQIO::addSearchPath(assestsPath + "mesh/");

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
					for (unsigned int i = 0 ; i < res.Size(); ++i)
					{
						Value & it = res[i];

						std::string prefix = "ResIDDef::";
						std::string name = it["name"].GetString();
						name = prefix + name;
						std::string url = it["url"].GetString();
						std::string abPath = assestsPath + url;
						ResType type = static_cast<ResType>(it["type"].GetInt());

						CQResConfig cfg(name, url, abPath, type);
						resMap_.insert(std::make_pair(name, cfg));
					}
				}
			}
		}
	}
}

