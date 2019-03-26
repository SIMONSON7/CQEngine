//*****************************************************************************
//
//! \file CQBevLoop.h
//! \brief Refer to https://github.com/FinneyTang/TsiU_AIToolkit_CSharp
//! \author qiu_hao
//! \date 2019/03/26 10:22.pm
//
//*****************************************************************************
#ifndef __CQBEVLOOP_H__
#define __CQBEVLOOP_H__

#include "CQBevNode.h"

NS_CQ_BEGIN

class CQBevLoop : public CQBevNode
{
public:
	const static int INFINITY_LOOP = -1;

public:
	CQBevLoop(CQBevNode * _parent, CQBevPrecondition * _precondition, int _loopCnt = INFINITY_LOOP);

	virtual ~CQBevLoop() = default;

public:
	virtual bool doEvaluate(const BevInParam &);

	virtual void doTransition(const BevInParam &);

	virtual BevRunningStatus doTick(const BevInParam &, BevOutParam &);

private:
	int loopCnt_;

	int curLoopCnt_;
};

NS_CQ_END

#endif /* __CQBEVLOOP_H__ */