#include <algorithm>
#include "CQBevPrioritySelector.h"

CQBevPrioritySelector::CQBevPrioritySelector(CQBevNode * _parent, CQBevPrecondition * _precondition)
	:
	CQBevNode(_parent, _precondition),
	curSelectedID_(-1),
	lastSelectedID_(-1)
{

}

bool CQBevPrioritySelector::doEvaluate(const BevInParam & _input)
{
	for each (auto it in children_)
	{
		if (it->evaluate(_input))
		{
			curSelectedID_ = it->getID();
			return true;
		}
	}

	return false;
}

void CQBevPrioritySelector::doTransition(const BevInParam & _input)
{
	if (lastSelectedID_ >= 0)
	{
		auto child = findChildByID(lastSelectedID_);
		if (child)
		{
			child->doTransition(_input);
		}
	}

	lastSelectedID_ = -1;
}

BevRunningStatus CQBevPrioritySelector::doTick(const BevInParam & _input, BevOutParam & _output)
{
	BevRunningStatus status = BevRunningStatus::FINISH;

	// DoTransition and Update lastSelectedID_ if necessary.
	if (curSelectedID_ != lastSelectedID_)
	{
		auto child = findChildByID(lastSelectedID_);
		if (child)
		{
			child->doTransition(_input);
		}
		lastSelectedID_ = curSelectedID_;
	}

	// Get running node and call DoTick().
	if (lastSelectedID_ >= 0)
	{
		auto child = findChildByID(lastSelectedID_);
		if (child)
		{
			status = child->doTick(_input, _output);
			if (status == BevRunningStatus::FINISH)
			{
				lastSelectedID_ = -1;
			}
		}
	}

	return status;
}
