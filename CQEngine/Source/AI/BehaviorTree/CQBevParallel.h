//*****************************************************************************
//
//! \file CQBevParallel.h
//! \brief Refer to https://github.com/FinneyTang/TsiU_AIToolkit_CSharp
//! \author qiu_hao
//! \date 2019/03/19 04:23.pm
//
//*****************************************************************************
#ifndef __CQBEVPARALLEL_H__
#define __CQBEVPARALLEL_H__

#include <vector>
#include "CQBevNode.h"

NS_CQ_BEGIN

enum class ParallelFinishCondition
{
	AND,
	OR,
};

class CQBevParallel : public CQBevNode
{
public:
	CQBevParallel(CQBevNode * _parent, CQBevPrecondition * _precondition);

	virtual ~CQBevParallel() = default;

public:
	virtual bool doEvaluate(const BevInParam &);

	virtual void doTransition(const BevInParam &);

	virtual BevRunningStatus doTick(const BevInParam &, BevOutParam &);

public:
	inline void setFinishCondition(ParallelFinishCondition _condition) { finishCondition_ = _condition; }

	inline ParallelFinishCondition getFinishCondition() const { return finishCondition_; }

private:
	ParallelFinishCondition finishCondition_;

	std::vector<BevRunningStatus> childRunningStatus_;
};

NS_CQ_END

#endif /* __CQBEVPARALLEL_H__ */