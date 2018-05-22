/*
*
*		qiu_hao		2018/05/21		11:33.pm
*/
#ifndef __CQSAFESTACK_H__
#define __CQSAFESTACK_H__

#include <memory>
#include "CQMacros.h"


NS_CQ_BEGIN

template <typename T>
class CQSafeStack
{
public:
	CQSafeStack();
	CQSafeStack(const CQSafeStack&);
private:
	CQSafeStack& operator=(const CQSafeStack&) = delete;
public:
	void push(T _val);
	bool try_push(T& _val);
	std::shared_ptr<T> try_pop();
	void wait_and_pop(T& value);
	bool empty() const;
};

NS_CQ_END

#endif /*__CQSAFESTACK_H__*/
