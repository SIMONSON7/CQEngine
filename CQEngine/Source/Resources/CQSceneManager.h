/*
*
*		qiu_hao		2018/08/18		11:21.pm
*/
#include <stack>
#include <memory>
#include "CQScene.h"

#ifndef __CQSCENEMANAGER_H__
#define __CQSCENEMANAGER_H__

NS_CQ_BEGIN

class CQSceneManager 
{
public:
	explicit CQSceneManager();

	virtual ~CQSceneManager();

public:
	static
	CQSceneManager *shareSceneManager();

	std::shared_ptr<CQScene> getCurRunningScene();

	std::shared_ptr<CQScene> registerStartScene();

public:
	//void pushScene();
	
	void cleanAndPushScene(std::shared_ptr<CQScene> _scene);

private:
	// non-copyable
	CQSceneManager(const CQSceneManager &) = delete;

	CQSceneManager& operator=(const CQSceneManager &) = delete;

private:
	std::vector<std::shared_ptr<CQScene>> scenes_;
};

NS_CQ_END

#define REGISTER_START_SCENE(CLASS_NAME) \
	bool userRegisterStartScene() \
	{ \
		std::shared_ptr<CLASS_NAME> sp = std::make_shared<CLASS_NAME>(); \
		CQSceneManager::shareSceneManager()->cleanAndPushScene(sp); \
		return true; \
	} \

#endif /* __CQSCENEMANAGER_H__ */