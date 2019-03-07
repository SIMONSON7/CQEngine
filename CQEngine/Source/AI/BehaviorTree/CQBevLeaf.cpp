#include "CQBevLeaf.h"

USING_NS_CQ

CQBevLeaf::CQBevLeaf(CQBevNode * _parent, CQBevPrecondition * _precondition)
	:
	CQBevNode(_parent, _precondition),
	isNeedExit_(false),
	leafStatus_(BevLeafStatus::READY)
{

}

void CQBevLeaf::doTransition(const BevInParam & _input)
{
	if (isNeedExit_)
	{
		onExit(_input, BevRunningStatus::TRANSITION);
	}

	setActiveNode(nullptr);
	//isNeedExit_ = false;
	leafStatus_ = BevLeafStatus::READY;
}

BevRunningStatus CQBevLeaf::doTick(const BevInParam & _input, BevOutParam & _output)
{
	BevRunningStatus runningState = BevRunningStatus::FINISH;

	switch (leafStatus_)
	{
	case CQEngine::BevLeafStatus::READY:
		onEnter(_input);
		leafStatus_ = BevLeafStatus::EXECUTING;
		break;
	case CQEngine::BevLeafStatus::EXECUTING:
		runningState = onExecute(_input, _output);
		//setActiveNode(this);
		if (runningState == BevRunningStatus::FINISH)
		{
			leafStatus_ = BevLeafStatus::FINISH;
		}
		break;
	case CQEngine::BevLeafStatus::FINISH:
		if (isNeedExit_)
		{
			onExit(_input, runningState);
		}
		leafStatus_ = BevLeafStatus::READY;
		//setActiveNode(nullptr);
		break;
	default:
		break;
	}

	return runningState;
}