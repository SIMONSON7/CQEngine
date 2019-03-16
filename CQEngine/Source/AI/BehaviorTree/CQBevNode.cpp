#include <algorithm>
#include "CQBevNode.h"

USING_NS_CQ;

CQBevNode::CQBevNode(CQBevNode * _parent, CQBevPrecondition * _precondition)
	:
	parent_(_parent),
	preconditon_(_precondition),
	activeChild_(nullptr),
	lastActiveChild_(nullptr),
	name_("DEFNAME"),
	id_(-1)
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

CQBevNode & CQBevNode::setPevcondition(CQBevPrecondition * _condition)
{
	CQASSERT(_condition);
	if (preconditon_ != _condition)
	{
		CQ_RAW_DELETE(preconditon_);
		preconditon_ = _condition;
	}

	return (*this);
}

void CQBevNode::setActiveNode(CQBevNode * _node)
{
	CQASSERT(_node);
	lastActiveChild_ = activeChild_;
	activeChild_ = _node;

	if (parent_)
	{
		parent_->setActiveNode(_node);
	}
}

bool CQBevNode::evaluate(const BevInParam & _input)
{
	return (preconditon_ == nullptr || preconditon_->externalCondition(_input)) && doEvaluate(_input);
}

void CQBevNode::transition(const BevInParam & _input)
{
	return doTransition(_input);
}

BevRunningStatus CQBevNode::tick(const BevInParam & _input, BevOutParam & _output)
{
	return doTick(_input, _output);
}

CQBevNode * CQBevNode::findChildByID(const int32_t _id)
{
	CQBevNode * ret = nullptr;
	auto it = std::find_if(children_.begin(), children_.end(),
		[=](CQBevNode *_node) { return _node->getID() == _id; });
	if (it != children_.end())
	{
		ret = *it;
	}
	return ret;
}