//*****************************************************************************
//
//! \file CQBevPrioritySelector.h
//! \brief Refer to https://github.com/FinneyTang/TsiU_AIToolkit_CSharp
//! \author qiu_hao
//! \date 2019/03/13 10:35.pm
//
//*****************************************************************************
#ifndef __CQBEVPRIORITYSELECTOR_H__
#define __CQBEVPRIORITYSELECTOR_H__

#include "CQBevNode.h"

NS_CQ_BEGIN

class CQBevPrioritySelector : public CQBevNode
{
public:
	CQBevPrioritySelector(CQBevNode * _parent, CQBevPrecondition * _precondition);

	virtual ~CQBevPrioritySelector() = default;

public:
	virtual bool doEvaluate(const BevInParam &);

	virtual void doTransition(const BevInParam &);

	virtual BevRunningStatus doTick(const BevInParam &, BevOutParam &);

protected:
	int32_t curSelectedID_;

	int32_t lastSelectedID_;
};

NS_CQ_END

#endif /* __CQBEVPRIORITYSELECTOR_H__ */