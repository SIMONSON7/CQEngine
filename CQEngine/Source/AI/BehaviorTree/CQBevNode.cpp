#include "CQBevNode.h"

USING_NS_CQ;

CQBevNode::CQBevNode(CQBevNode * _parent, CQBevPrecondition * _precondition)
{

}

CQBevNode::~CQBevNode()
{

}

CQBevNode & CQBevNode::addChild(CQBevNode * _child)
{
	CQASSERT(_child);
	children_.push_back(_child);
	return (*this);
}


