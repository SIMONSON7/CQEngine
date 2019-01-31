//*****************************************************************************
//
//! \file CQResManager.h
//! \brief 
//! \author qiu_hao
//! \date 2019/01/25 05:29.pm
//
//*****************************************************************************
#ifndef __CQRESMANAGER_H__
#define __CQRESMANAGER_H__

#include <string>
//#include <unordered_map>
#include <map>
#include <memory>
#include "CQMacros.h"
#include "CQNoncopyable.h"
#include "ResID.h"
#include "CQResI.h"

NS_CQ_BEGIN

struct CQResConfig
{
	CQResConfig() {}

	CQResConfig(std::string & _name, std::string & _path, 
		std::string & _abPath, ResType _type)
		:
		name_(_name),
		path_(_path),
		abPath_(_abPath),
		type_(_type)
	{}

	std::string name_;
	std::string path_;
	std::string abPath_;
	ResType type_;
};

class CQResManager : private CQNoncopyable
{
public:
	typedef std::shared_ptr<CQResI> SpCQResI;

public:
	~CQResManager();

public:
	SpCQResI getRes(const ResID _resID);

	SpCQResI getRes(const std::string & _path);

	bool destroyRes(const ResID _resID);

	bool destroyRes(const std::string & _path);

public:
	// getResAsync();

public:
	// SpCQResI poolGetRes(const ResID _resID);

	// ResID getResIDByName(const std::string & _name);
private:
	friend class CQCore;

	explicit CQResManager();

private:
	void __parseResCfg();

private:
	std::map<ResID, CQResConfig> resMap_;

	std::map<std::string, SpCQResI> resLoadedMap_;

	std::map<std::string, SpCQResI> resDontDestroyMap_;
};

NS_CQ_END

#endif /* __CQRESMANAGER_H__ */
