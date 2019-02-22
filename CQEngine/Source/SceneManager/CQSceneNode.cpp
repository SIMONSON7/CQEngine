#include <algorithm>
#include "CQTransform.h"
#include "CQObject.h"
#include "CQSceneNode.h"
#include "CQMemory.h"

USING_NS_CQ

CQSceneNode* CQSceneNode::s_root_ = CQ_NEW(CQSceneNode, nullptr, nullptr, "ROOT");

CQSceneNode::CQSceneNode(CQSceneNode * _parent, CQObject* _obj, const string & _name)
	:
	name_(_name),
	isDirty_(false),
	isVisited_(false)
{
	// obj
	if (_obj)
	{
		obj_ = _obj;
	}
	else
	{
		obj_ = CQ_NEW(CQObject);
		obj_->setName("DEFAULT");
	}

	// parent
	if (_parent)
	{
		parent_ = _parent;
		parent_->attachChild(this);
	}
	else
	{
		parent_ = nullptr;
	}

	// children
	children_.clear();
}

CQSceneNode::~CQSceneNode()
{
	if (parent_)
	{
		parent_->detach(name_);
		parent_ = nullptr;
	}

	CQ_DELETE(obj_, CQObject);
	for each (auto child in children_)
	{
		CQ_DELETE(child, CQSceneNode);
	}
}

bool CQSceneNode::attachChild(CQSceneNode* _child)
{
	CQASSERT(_child);
	children_.push_back(_child);
	__updateSubGraph(this);
	return true;
}

void CQSceneNode::attachObj(CQObject* _obj)
{
	CQASSERT(_obj);
	obj_ = _obj;
}

bool CQSceneNode::detach(const string & _childName)
{
	auto itr = std::find_if(children_.begin(), children_.end(), 
		[=](CQSceneNode* node) { return node->getName() == _childName; });

	if (itr != children_.end())
	{
		children_.erase(itr);
		//__updateSubGraph(*itr);
		return true;
	}
	return false;
}

void CQSceneNode::detachChildren()
{
	for each (auto child in children_)
	{
		child->parent_ = nullptr;
	}

	children_.clear();
}

void CQSceneNode::__updateSubGraph(CQSceneNode* _root)
{
	if (_root == nullptr)
	{
		return;
	}

	if (_root->getParent())
	{
		auto obj = _root->getObj();
		if (obj)
		{
			auto trans = obj->getTransform();
			trans->setParent(_root->getParent()->getObj()->getTransform().get());
		}
	}

	for each (auto child in _root->children_)
	{
		__updateSubGraph(child);
	}
}