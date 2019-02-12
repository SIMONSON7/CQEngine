#include "CQObject.h"
#include "CQCuller.h"
#include "CQSceneNode.h"

USING_NS_CQ

CQCuller::~CQCuller()
{

}

CQCuller::CQCuller()
{

}

std::vector<CQObject*> CQCuller::getVisibleObjs()
{
	visibleObjs_.clear();

	// DFS
	std::vector<CQSceneNode*> stack;
	stack.push_back(CQSceneNode::s_root_);
	while (!stack.empty())
	{
		CQSceneNode * node = stack.back();
		stack.pop_back();

		if (!node->isVisited_)
		{
			node->isVisited_ = true;
			if (__isVisible(node->getObj()))
			{
				visibleObjs_.push_back(node->getObj());
			}

			for each (auto child in node->getChildren())
			{
				stack.push_back(child);
			}

			// Scene graph is actually a tree, 
			// so can set isVisited_ by false value.
			node->isVisited_ = false;
		}
	}

	return visibleObjs_;
}

bool CQCuller::__isVisible(CQObject * _obj)
{
	if (!_obj)
	{
		return false;
	}

	if (!_obj->getVisible())
	{
		return false;
	}

	return true;
}