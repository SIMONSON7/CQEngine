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

}

void CQBevSequence::doTransition(const BevInParam & _input)
{

}

BevRunningStatus CQBevSequence::doTick(const BevInParam & _input, BevOutParam & _output)
{

}