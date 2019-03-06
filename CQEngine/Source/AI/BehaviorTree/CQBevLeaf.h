//*****************************************************************************
//
//! \file CQBevLeaf.h
//! \brief Refer to https://github.com/FinneyTang/TsiU_AIToolkit_CSharp
//! \author qiu_hao
//! \date 2019/03/05 06:27.pm
//
//*****************************************************************************
#ifndef __CQBEVLEAF_H__
#define __CQBEVLEAF_H__

#include "CQBevNode.h"

NS_CQ_BEGIN

class CQBevLeaf : public CQBevNode
{
public:


public:
	virtual bool doEvaluate(const BevInParam &)
	{
		return true;
	}

	virtual void doTransition(const BevInParam &)
	{

	}

	virtual BevRunningStatus doTick(const BevInParam &, BevOutParam &)
	{
		return BevRunningStatus::FINISH;
	}

private:

};

NS_CQ_END

#endif /* __CQBEVLEAF_H__ */