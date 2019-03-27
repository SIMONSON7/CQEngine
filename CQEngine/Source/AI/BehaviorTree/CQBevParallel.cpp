#include "CQBevParallel.h"

USING_NS_CQ;

CQBevParallel::CQBevParallel(CQBevNode * _parent, CQBevPrecondition * _precondition)
	:
	CQBevNode(_parent, _precondition),
	finishCondition_(ParallelFinishCondition::OR)
{
	__resetChildrenRunningStatusMap(BevRunningStatus::EXECUTING);
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

BevRunningStatus CQBevParallel::doTick(const BevInParam & _input, BevOutParam & _output)
{
	if (finishCondition_ == ParallelFinishCondition::OR)
	{
		for each (auto child in children_)
		{
			if (childRunningStatusMap_[child->getID()] == BevRunningStatus::EXECUTING)
			{
				childRunningStatusMap_[child->getID()] = child->tick(_input, _output);
			}
			// Find ONE node's tick() return FINISH.
			//if (childRunningStatusMap_[child->getID()] == BevRunningStatus::FINISH ||
			//	childRunningStatusMap_[child->getID()] == BevRunningStatus::ERROR_TRANSITION)
			if (childRunningStatusMap_[child->getID()] != BevRunningStatus::EXECUTING)
			{
				__resetChildrenRunningStatusMap(CQEngine::BevRunningStatus::EXECUTING);
				return CQEngine::BevRunningStatus::FINISH;
			}
		}
	}
	else if (finishCondition_ == ParallelFinishCondition::AND)
	{
		int finishedChildCnt = 0;

		for each (auto child in children_)
		{
			// tick
			if (childRunningStatusMap_[child->getID()] == BevRunningStatus::EXECUTING)
			{
				childRunningStatusMap_[child->getID()] = child->tick(_input, _output);
			}

			// check result.
			if (childRunningStatusMap_[child->getID()] != BevRunningStatus::EXECUTING)
			{
				++finishedChildCnt;
			}
		}
		
		if (finishedChildCnt == children_.size())
		{
			__resetChildrenRunningStatusMap(CQEngine::BevRunningStatus::EXECUTING);
			return CQEngine::BevRunningStatus::FINISH;
		}
	}

	return BevRunningStatus::EXECUTING;
}

void CQBevParallel::__resetChildrenRunningStatusMap(BevRunningStatus _status)
{
	childRunningStatusMap_.clear();

	for each (auto child in children_)
	{
		childRunningStatusMap_.insert({ child->getID(), _status });
	}
}