#include "CQBevLoop.h"

USING_NS_CQ

CQBevLoop::CQBevLoop(CQBevNode * _parent, CQBevPrecondition * _precondition, int _loopCnt)
	:
	CQBevNode(_parent, _precondition),
	loopCnt_(_loopCnt),
	curLoopCnt_(0)
{

}

bool CQBevLoop::doEvaluate(const BevInParam & _input)
{
	bool checkLoopCnt = (loopCnt_ == INFINITY_LOOP ||
						curLoopCnt_ < loopCnt_);
	if (!checkLoopCnt)
	{
		return false;
	}

	auto target = *children_.begin();
	if (target)
	{
		return target->evaluate(_input);
	}
	return false;
}

void CQBevLoop::doTransition(const BevInParam & _input)
{
	auto target = *children_.begin();
	if (target)
	{
		return target->transition(_input);
	}
	curLoopCnt_ = 0;
}

BevRunningStatus CQBevLoop::doTick(const BevInParam & _input, BevOutParam & _output)
{
	CQASSERT(children_.size());

	BevRunningStatus status = BevRunningStatus::FINISH;
	auto target = *children_.begin();
	if (target)
	{
		status = target->tick(_input, _output);
		if (status == BevRunningStatus::FINISH)
		{
			if (loopCnt_ != INFINITY_LOOP)
			{
				curLoopCnt_++;
				if (curLoopCnt_ < loopCnt_ || loopCnt_ == INFINITY_LOOP)
				{
					status = BevRunningStatus::EXECUTING;
				}
			}
		}
	}
	return status;
}