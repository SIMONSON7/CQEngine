/*
*
*		qiu_hao		2018/05/21		11:33.pm
*/
#ifndef __CQSAFESTACK_H__
#define __CQSAFESTACK_H__

#include <memory>
#include <mutex>
#include <stack>
#include "CQMacros.h"

NS_CQ_BEGIN

template <typename TYPE>
class CQSafeStack
{
public:
	CQSafeStack();
	CQSafeStack(const CQSafeStack&);
	virtual ~CQSafeStack();

private:
	CQSafeStack& operator=(const CQSafeStack&) = delete;

public:
	void push(TYPE _val);
	// if pop fail, then return false;
	bool try_pop(TYPE& _val);
	// if pop fail, then return null;
	std::shared_ptr<TYPE> try_pop();
	void wait_and_pop(TYPE& _val);
	bool empty() const;

private:
	std::mutex mut_;
	std::stack<TYPE> stack_;
	std::condition_variable data_cond_;
};

#include "CQSafeStack.inl"

NS_CQ_END

#endif /*__CQSAFESTACK_H__*/
