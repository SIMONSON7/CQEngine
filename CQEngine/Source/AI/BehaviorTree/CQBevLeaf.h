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

enum class BevLeafStatus
{
	READY = 0,
	EXECUTING = 1,
	FINISH = 2,
};

class CQBevLeaf : public CQBevNode
{
public:
	CQBevLeaf(CQBevNode * _parent, CQBevPrecondition * _precondition);

	virtual ~CQBevLeaf() = default;

public:
	// Leaf node NO need doEvaluate();
	virtual void doTransition(const BevInParam &);

	virtual BevRunningStatus doTick(const BevInParam &, BevOutParam &);

public:
	virtual void onEnter(const BevInParam & _input) {}

	virtual BevRunningStatus onExecute(const BevInParam & _input, BevOutParam & _output) { return BevRunningStatus::FINISH; }

	virtual void onExit(const BevInParam & _input, BevRunningStatus _exitStatus) {}

private:
	// If has called onEnter(), it need to call onExit();
	bool isNeedExit_;

	BevLeafStatus leafStatus_;
};

NS_CQ_END

#endif /* __CQBEVLEAF_H__ */