#include "CQBevNonePrioritySelector.h"

USING_NS_CQ;

bool CQBevNonePrioritySelector::doEvaluate(const BevInParam & _input)
{
	if (lastSelectedID_ >= 0)
	{
		auto child = findChildByID(lastSelectedID_);
		if (child && child->doEvaluate(_input))
		{
			return true;
		}
	}

	return CQBevPrioritySelector::doEvaluate(_input);
}