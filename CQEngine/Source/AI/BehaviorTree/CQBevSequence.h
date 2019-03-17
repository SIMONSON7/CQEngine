//*****************************************************************************
//
//! \file CQBevSequence.h
//! \brief Refer to https://github.com/FinneyTang/TsiU_AIToolkit_CSharp
//! \author qiu_hao
//! \date 2019/03/17 10:25.pm
//
//*****************************************************************************
#ifndef __CQBEVSEQUENCE_H__
#define __CQBEVSEQUENCE_H__

#include "CQBevNode.h"

NS_CQ_BEGIN

class CQBevSequence : public CQBevNode
{
public:
	CQBevSequence(CQBevNode * _parent, CQBevPrecondition * _precondition);

	virtual ~CQBevSequence() = default;

public:
	virtual bool doEvaluate(const BevInParam &);

	virtual void doTransition(const BevInParam &);

	virtual BevRunningStatus doTick(const BevInParam &, BevOutParam &);

private:
	int32_t curSelectedID_;
};

NS_CQ_END

#endif /* __CQBEVSEQUENCE_H__ */
