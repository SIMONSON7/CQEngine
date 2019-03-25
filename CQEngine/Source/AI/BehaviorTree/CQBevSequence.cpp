#include "CQBevSequence.h"

USING_NS_CQ;

CQBevSequence::CQBevSequence(CQBevNode * _parent, CQBevPrecondition * _precondition)
	:
	CQBevNode(_parent, _precondition),
	curSelectedID_(-1)
{

}

bool CQBevSequence::doEvaluate(const BevInParam & _input)
{
	// At least ONE.
	CQASSERT(children_.size());

	CQBevNode * targetNode = findChildByID(curSelectedID_);
	if (targetNode == nullptr)
	{
		targetNode = *children_.begin();
	}

	if (targetNode->evaluate(_input))
	{
		return true;
	}
	return false;
}

void CQBevSequence::doTransition(const BevInParam & _input)
{
	CQBevNode * targetNode = findChildByID(curSelectedID_);
	if (targetNode)
	{
		targetNode->transition(_input);
	}
	curSelectedID_ = -1;
}

BevRunningStatus CQBevSequence::doTick(const BevInParam & _input, BevOutParam & _output)
{
	CQASSERT(children_.size());

	BevRunningStatus status = BevRunningStatus::FINISH;
	
	CQBevNode * targetNode = findChildByID(curSelectedID_);
	if (targetNode == nullptr)
	{
		targetNode = *children_.begin();
	}

	status = targetNode->tick(_input, _output);
	// Handler error.
	if (status <= BevRunningStatus::ERROR_TRANSITION)
	{
		curSelectedID_ = -1;
		return status;
	}
	else if (status == BevRunningStatus::FINISH)
	{
		// Get next node.
		curSelectedID_++;
		if (findChildByID(curSelectedID_))
		{
			status = BevRunningStatus::EXECUTING;
		}
		// Reaching the end.
		else
		{
			curSelectedID_ = -1;
		}
	}
	// status == BevRunningStatus::EXECUTING
	return status;
}