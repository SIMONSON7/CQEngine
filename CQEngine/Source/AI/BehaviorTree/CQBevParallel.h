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

#include <unordered_map>
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
	inline CQBevParallel& setFinishCondition(ParallelFinishCondition _condition) { finishCondition_ = _condition; return *this; }

	inline ParallelFinishCondition getFinishCondition() const { return finishCondition_; }

private:
	ParallelFinishCondition finishCondition_;

	std::unordered_map<int32_t, BevRunningStatus> childRunningStatusMap_;
};

NS_CQ_END

#endif /* __CQBEVPARALLEL_H__ */