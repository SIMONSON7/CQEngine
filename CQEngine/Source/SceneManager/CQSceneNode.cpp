#include "CQSceneNode.h"

USING_NS_CQ

CQSceneNode::CQSceneNode(CQSceneNode* _parent, const string& _name)
	:
	parent_(_parent),
	name_(_name)
{

}

CQSceneNode::~CQSceneNode()
{

}

void CQSceneNode::attachParent(CQSceneNode* _parent)
{

}

void CQSceneNode::attachChild(CQSceneNode* _child)
{

}

void CQSceneNode::attachObj(CQObject* _obj)
{

}

void CQSceneNode::detach(const string& _childName)
{

}

void CQSceneNode::detachChildren()
{

}