/*
*
*		qiu_hao		2018/08/18		11:21.pm
*/
#include <vector>
#include <memory>
#include "CQMacros.h"

#ifndef __CQSCENEMANAGER_H__
#define __CQSCENEMANAGER_H__

NS_CQ_BEGIN

class CQScene;

class CQSceneManager 
{
public:
	explicit CQSceneManager();

	virtual ~CQSceneManager();

public:
	static
	CQSceneManager *shareSceneManager();

	//std::shared_ptr<CQScene> getCurRunningScene();

private:
	// non-copyable
	CQSceneManager(const CQSceneManager &) = delete;

	CQSceneManager& operator=(const CQSceneManager &) = delete;

private:
	std::vector<std::shared_ptr<CQScene>> scenes_;
};

NS_CQ_END

#endif /* __CQSCENEMANAGER_H__ */