//*****************************************************************************
//
//! \file CQBevNonePrioritySelector.h
//! \brief Refer to https://github.com/FinneyTang/TsiU_AIToolkit_CSharp
//! \author qiu_hao
//! \date 2019/03/17 10:03.pm
//
//*****************************************************************************
#ifndef __CQBEVNONEPRIORITYSELECTOR_H__
#define __CQBEVNONEPRIORITYSELECTOR_H__

#include "CQBevPrioritySelector.h"

NS_CQ_BEGIN

class CQBevNonePrioritySelector : public CQBevPrioritySelector
{
public:
	CQBevNonePrioritySelector(CQBevNode * _parent, CQBevPrecondition * _precondition)
		:
		CQBevPrioritySelector(_parent, _precondition)
	{}

	virtual ~CQBevNonePrioritySelector() {}

public:
	virtual bool doEvaluate(const BevInParam & _input);
};

NS_CQ_END

#endif /* __CQBEVNONEPRIORITYSELECTOR_H__ */



