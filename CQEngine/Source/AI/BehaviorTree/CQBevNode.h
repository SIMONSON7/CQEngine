//*****************************************************************************
//
//! \file CQBevNode.h
//! \brief Refer to https://github.com/FinneyTang/TsiU_AIToolkit_CSharp
//! \author qiu_hao
//! \date 2019/03/04 05:19.pm
//
//*****************************************************************************
#ifndef __CQBEVNODE_H__
#define __CQBEVNODE_H__

#include <string>
#include <vector>
#include "CQMacros.h"
#include "CQAny.h"

NS_CQ_BEGIN

class CQBevPrecondition;

class CQBevNode
{
public:
	CQBevNode(CQBevNode * _parent, CQBevPrecondition * _precondition);

	virtual ~CQBevNode();

public:
	CQBevNode & addChild(CQBevNode * _child);

	CQBevNode & setPevcondition(CQBevPrecondition * _condition);
	
public:
	inline void setName(const std::string & _name)
	{
		name_ = _name;
	}

	inline const std::string & getName() const
	{
		return name_;
	}

	inline CQBevNode * getLastActiveNode() const
	{
		return lastActiveChild_;
	}

protected:
	inline void setParent(CQBevNode * _parent)
	{
		parent_ = _parent;
	}

private:
	std::vector<CQBevNode*> children_;

	CQBevNode * parent_;

	CQBevPrecondition * preconditon_;

	CQBevNode * activeChild_;

	CQBevNode * lastActiveChild_;

	std::string name_;
};

NS_CQ_END

#endif /* __CQBEVNODE_H__ */






