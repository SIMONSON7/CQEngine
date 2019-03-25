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
		onExit(_input, BevRunningStatus::ERROR_TRANSITION);
	}
	isNeedExit_ = false;

	setActiveNode(nullptr);
	leafStatus_ = BevLeafStatus::READY;
}

BevRunningStatus CQBevLeaf::doTick(const BevInParam & _input, BevOutParam & _output)
{
	BevRunningStatus runningState = BevRunningStatus::FINISH;

	switch (leafStatus_)
	{
	case CQEngine::BevLeafStatus::READY:
		onEnter(_input);
		isNeedExit_ = true;

		setActiveNode(this);
		leafStatus_ = BevLeafStatus::EXECUTING;
		break;
	case CQEngine::BevLeafStatus::EXECUTING:
		setActiveNode(this);
		runningState = onExecute(_input, _output);
		if (runningState == BevRunningStatus::FINISH ||
			// Less than 0 means ERRO occur.
			static_cast<int>(runningState) < 0)
		{
			leafStatus_ = BevLeafStatus::FINISH;
		}
		break;
	case CQEngine::BevLeafStatus::FINISH:
		if (isNeedExit_)
		{
			onExit(_input, runningState);
		}
		isNeedExit_ = false;

		setActiveNode(nullptr);
		leafStatus_ = BevLeafStatus::READY;
		break;
	default:
		break;
	}
	return runningState;
}