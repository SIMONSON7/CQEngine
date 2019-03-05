//*****************************************************************************
//
//! \file CQBevPrecondition.h
//! \brief Refer to https://github.com/FinneyTang/TsiU_AIToolkit_CSharp
//! \author qiu_hao
//! \date 2019/03/04 10:23.pm
//
//*****************************************************************************
#ifndef __CQBEVPRECONDITION_H__
#define __CQBEVPRECONDITION_H__

#include "CQAny.h"

using BevInParam = CQAny;
using BevOutParam = CQAny;

class CQBevPrecondition
{
public:
	virtual bool externalCondition(const BevInParam & _input) const = 0;
};

class CQBevPreconditionTRUE : public CQBevPrecondition
{
public:
	virtual bool externalCondition(const BevInParam & _input) const
	{
		return true;
	}
};

class CQBevPreconditionFALSE : public CQBevPrecondition
{
public:
	virtual bool externalCondition(const BevInParam & _input) const
	{
		return false;
	}
};

class CQBevPreconditionNOT : public CQBevPrecondition
{
public:
	CQBevPreconditionNOT(CQBevPrecondition * _lhs)
		: 
		lhs_(_lhs)
	{}

	~CQBevPreconditionNOT() 
	{
		CQ_RAW_DELETE(lhs_);
	}

	virtual bool externalCondition(const BevInParam & _input) const 
	{
		return !lhs_->externalCondition(_input);
	}

private:
	CQBevPrecondition * lhs_;
};

class CQBevPreconditionAND : public CQBevPrecondition
{
public:
	CQBevPreconditionAND(CQBevPrecondition * _lhs, CQBevPrecondition * _rhs)
		:
		lhs_(_lhs),
		rhs_(_rhs)
	{}

	~CQBevPreconditionAND()
	{
		CQ_RAW_DELETE(lhs_);
		CQ_RAW_DELETE(rhs_);

	}

	virtual bool externalCondition(const BevInParam & _input) const
	{
		return lhs_->externalCondition(_input) && rhs_->externalCondition(_input);
	}

private:
	CQBevPrecondition * lhs_;
	CQBevPrecondition * rhs_;
};

class CQBevPreconditionOR : public CQBevPrecondition
{
public:
	CQBevPreconditionOR(CQBevPrecondition * _lhs, CQBevPrecondition * _rhs)
		:
		lhs_(_lhs),
		rhs_(_rhs)
	{}

	~CQBevPreconditionOR()
	{
		CQ_RAW_DELETE(lhs_);
		CQ_RAW_DELETE(rhs_);

	}

	virtual bool externalCondition(const BevInParam & _input) const
	{
		return lhs_->externalCondition(_input) || rhs_->externalCondition(_input);
	}

private:
	CQBevPrecondition * lhs_;
	CQBevPrecondition * rhs_;
};

class CQBevPreconditionXOR : public CQBevPrecondition
{
public:
	CQBevPreconditionXOR(CQBevPrecondition * _lhs, CQBevPrecondition * _rhs)
		:
		lhs_(_lhs),
		rhs_(_rhs)
	{}

	~CQBevPreconditionXOR()
	{
		CQ_RAW_DELETE(lhs_);
		CQ_RAW_DELETE(rhs_);

	}

	virtual bool externalCondition(const BevInParam & _input) const
	{
		return lhs_->externalCondition(_input) ^ rhs_->externalCondition(_input);
	}

private:
	CQBevPrecondition * lhs_;
	CQBevPrecondition * rhs_;
};

#endif /* __CQBEVPRECONDITION_H__ */