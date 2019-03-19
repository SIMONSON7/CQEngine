#include "CQBevParallel.h"

USING_NS_CQ;

CQBevParallel::CQBevParallel(CQBevNode * _parent, CQBevPrecondition * _precondition)
	:
	CQBevNode(_parent, _precondition),
	finishCondition_(ParallelFinishCondition::OR)
{
	for each (auto child in children_)
	{
		childRunningStatusMap_.insert({child->getID(), BevRunningStatus::EXECUTING});
	}
}

bool CQBevParallel::doEvaluate(const BevInParam & _input)
{
	// Must every child node can evaluate().
	for each (auto child in children_)
	{
		if (childRunningStatusMap_[child->getID()] == BevRunningStatus::EXECUTING)
		{
			if (!child->evaluate(_input))
			{
				return false;
			}
		}
	}
	return true;
}

void CQBevParallel::doTransition(const BevInParam & _input)
{
	for each (auto child in children_)
	{
		child->transition(_input);
		childRunningStatusMap_[child->getID()] = BevRunningStatus::EXECUTING;
	}
}

BevRunningStatus CQBevParallel::doTick(const BevInParam &, BevOutParam &)
{

}