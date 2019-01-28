#include "CQSceneManager.h"
#include "CQMemory.h"
#include "CQSceneNode.h"

USING_NS_CQ

bool userRegisterStartScene();

CQSceneManager::CQSceneManager()
{

}

CQSceneManager::~CQSceneManager()
{

}

CQSceneManager *CQSceneManager::shareSceneManager()
{
	static CQSceneManager s_sceneMgr;
	return &s_sceneMgr;
}

std::shared_ptr<CQScene> CQSceneManager::registerStartScene()
{
	if (userRegisterStartScene())
	{
		return *(scenes_.begin());
	}
	return std::make_shared<CQScene>();
}

std::shared_ptr<CQScene> CQSceneManager::getCurRunningScene()
{
	if (scenes_.empty())
	{
		return std::make_shared<CQScene>();
	}
	else
	{
		// if (*(scenes_.begin())-> isActive())
		return *(scenes_.begin());
	}
}

void CQSceneManager::cleanAndPushScene(std::shared_ptr<CQScene> _scene)
{
	CQASSERT(_scene);
	scenes_.clear();
	scenes_.push_back(_scene);
}

void CQSceneManager::cleanAllScene()
{
	for each (auto scene in scenes_)
	{
		scene->onDestory();
	}

	// CQSceneNode::s_root_ shared by every scene.
	CQ_DELETE(CQSceneNode::s_root_, CQSceneNode);
}