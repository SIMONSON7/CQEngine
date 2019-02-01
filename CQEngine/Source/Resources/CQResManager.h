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
	SpCQResI getRes(const std::string & _resName);

	bool destroyRes(const std::string & _resName);

public:
	// getResAsync();

	// SpCQResI poolGetRes(const ResID _resID);

	// ResID getResIDByName(const std::string & _name);

	// CPP No support reflection.
	/*SpCQResI getRes(const ResID _resID);*/
	/*bool destroyRes(const ResID _resID);*/

private:
	friend class CQCore;

	explicit CQResManager();

private:
	void __parseResCfg();

private:
	// name : cfg
	std::map<std::string, CQResConfig> resMap_;

	// path : res
	std::map<std::string, SpCQResI> resLoadedMap_;

	// path : res
	std::map<std::string, SpCQResI> resDontDestroyMap_;
};

NS_CQ_END

#endif /* __CQRESMANAGER_H__ */
