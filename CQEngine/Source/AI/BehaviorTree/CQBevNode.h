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
#include "CQBevPrecondition.h"

NS_CQ_BEGIN

class CQBevNode
{
public:
	CQBevNode(CQBevNode * _parent, CQBevPrecondition * _precondition);

	virtual ~CQBevNode();

public:
	CQBevNode & addChild(CQBevNode * _child);

	CQBevNode & setPevcondition(CQBevPrecondition * _condition);

	void setActiveNode(CQBevNode * _node);

public:
	bool evaluate(const BevInParam & _input);

	void transition(const BevInParam & _input);

	BevRunningStatus tick(const BevInParam & _input, BevOutParam & _output);

public:
	virtual bool doEvaluate(const BevInParam &) { return true; }

	virtual void doTransition(const BevInParam &) {}

	virtual BevRunningStatus doTick(const BevInParam &, BevOutParam &) { return BevRunningStatus::FINISH; }

public:
	inline void setName(const std::string & _name) { name_ = _name; }

	inline const std::string & getName() const { return name_; }

	inline CQBevNode * getLastActiveNode() const { return lastActiveChild_; }

	inline void setID(const int32_t _id) { id_ = _id; }

	inline int32_t getID() const { return id_; }

protected:
	inline void setParent(CQBevNode * _parent) { parent_ = _parent; }

protected:
	std::vector<CQBevNode*> children_;

	CQBevNode * parent_;

	CQBevPrecondition * preconditon_;

	// Active Node just for Debugi.
	CQBevNode * activeChild_;

	CQBevNode * lastActiveChild_;

	std::string name_;

	int32_t id_;
};

NS_CQ_END

#endif /* __CQBEVNODE_H__ */






