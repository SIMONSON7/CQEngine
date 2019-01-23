#include <algorithm>
#include "CQTransform.h"
#include "CQObject.h"
#include "CQSceneNode.h"
#include "CQMemory.h"

USING_NS_CQ

CQSceneNode* CQSceneNode::s_root_ = CQ_NEW(CQSceneNode, nullptr, nullptr, "ROOT");

CQSceneNode::CQSceneNode(CQSceneNode* _parent, CQObject* _obj, const string & _name)
	:
	parent_(_parent),
	obj_(_obj),
	name_(_name),
	visiable_(true)
{

}

CQSceneNode::~CQSceneNode()
{
	visiable_ = false;

	if (parent_)
	{
		parent_->detach(name_);
	}

	CQ_DELETE(obj_, CQObject);
	for each (auto child in children_)
	{
		CQ_DELETE(child, CQSceneNode);
	}
}

bool CQSceneNode::attachParent(CQSceneNode* _parent)
{
	if (_parent == nullptr || parent_ == _parent)
	{
		return false;
	}

	if (parent_)
	{
		parent_->detach(name_);
	}
	_parent->attachChild(this);
	return true;
}

bool CQSceneNode::attachChild(CQSceneNode* _child)
{
	CQASSERT(_child);
	children_.push_back(_child);
	_child->parent_ = this;
	__updateGraph(this);
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
		(*itr)->parent_ = nullptr;
		__updateGraph(*itr);
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

void CQSceneNode::__updateGraph(CQSceneNode* _root)
{
	if (_root == nullptr)
	{
		return;
	}

	if (_root->getParent() && _root->getParent()->getObj())
	{
		auto obj = _root->getObj();
		if (obj)
		{
			auto sp = obj->getTransform();
			sp->setParent(_root->getParent()->getObj()->getTransform().get());
		}
	}

	for each (auto child in children_)
	{
		__updateGraph(child);
	}
}