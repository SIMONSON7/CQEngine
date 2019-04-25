#include <vector>
#include "CQMemory.h"
#include "CQSceneNode.h"
#include "CQSceneManager.h"

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
	// CQSceneNode::s_root_ shared by all scenes.
	for each (auto scene in scenes_)
	{
		scene->onDestory();
	}
	
	// Level of traversal.
	std::vector<CQSceneNode*> queue;
	std::vector<CQSceneNode*> stack;
	queue.push_back(CQSceneNode::s_root_);

	while (!queue.empty())
	{
		auto front = queue.begin();
		auto node = *front;
		queue.erase(front);
		for each (auto child in node->getChildren())
		{
			queue.push_back(child);
		}
		
		stack.push_back(node);
	}

	while (!stack.empty())
	{
		auto top = stack.begin();
		CQ_DELETE((*top), CQSceneNode);
		stack.erase(top);
	}
}