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

void CQBevPrioritySelector::doTransition(const BevInParam &)
{

}

BevRunningStatus CQBevPrioritySelector::doTick(const BevInParam &, BevOutParam &)
{

}
