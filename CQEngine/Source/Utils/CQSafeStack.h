//*****************************************************************************
//
//! \file CQSafeStack.h
//! \brief The stack of thread safe.
//! \author qiu_hao
//! \date 2018/05/21 11:33.pm
//
//*****************************************************************************

#ifndef __CQSAFESTACK_H__
#define __CQSAFESTACK_H__

#include <memory>
#include <mutex>
#include <stack>
#include "CQMacros.h"
#include "CQNoncopyable.h"

NS_CQ_BEGIN

template <typename TYPE>
class CQSafeStack : private CQNoncopyable
{
public:
	CQSafeStack();

	CQSafeStack(const CQSafeStack&);

	virtual ~CQSafeStack();

public:
	void push(TYPE _val);

	//*****************************************************************************
	//
	//! \brief Trying to pop element form the stack.
	//! \param [out] _val If the container is not empty, 
	//	the top of the stack will pop up.
	//! \retval Is it successfully popped up.
	//
	//*****************************************************************************
	bool try_pop(TYPE& _val);

	//*****************************************************************************
	//
	//! \brief Trying to pop element form the stack.
	//! \retval Return the top element of the stack.
	//  If there is no element,will return null.
	//
	//*****************************************************************************
	std::shared_ptr<TYPE> try_pop();

	void wait_and_pop(TYPE& _val);

	bool empty() const;

private:
	mutable std::mutex mut_;
	std::stack<TYPE> stack_;
	std::condition_variable data_cond_;
};

#include "CQSafeStack.inl"

NS_CQ_END

#endif /*__CQSAFESTACK_H__*/
