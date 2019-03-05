//*****************************************************************************
//
//! \file CQBevTree.h
//! \brief Refer to https://github.com/FinneyTang/TsiU_AIToolkit_CSharp
//! \author qiu_hao
//! \date 2019/03/04 10:26.pm
//
//*****************************************************************************
#ifndef __CQBEVTREE_H__
#define __CQBEVTREE_H__

#include "CQMacros.h"
#include "CQAny.h"

NS_CQ_BEGIN

using BevInParam = CQAny;
using BevOutParam = CQAny;

enum class  BevRunningStatus
{
	EXECUTING = 0,
	FINISH = 1,
	ERROR_TRANSITION = -1,
};

NS_CQ_END

#endif /* __CQBEVTREE_H__ */