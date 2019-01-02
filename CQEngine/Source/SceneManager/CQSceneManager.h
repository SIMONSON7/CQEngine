/*
*
*		qiu_hao		2018/08/18		11:21.pm
*/
#ifndef __CQSCENEMANAGER_H__
#define __CQSCENEMANAGER_H__

#include <stack>
#include <memory>
#include "CQMacros.h"
#include "CQNoncopyable.h"
#include "CQScene.h"

NS_CQ_BEGIN

class CQSceneManager : private CQNoncopyable
{
public:
	virtual ~CQSceneManager();

public:
	static
	CQSceneManager *shareSceneManager();

	std::shared_ptr<CQScene> getCurRunningScene();

	std::shared_ptr<CQScene> registerStartScene();

public:
	//void pushScene();
	
	void cleanAndPushScene(std::shared_ptr<CQScene> _scene);

	void cleanAllScene();

private:
	explicit CQSceneManager();

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