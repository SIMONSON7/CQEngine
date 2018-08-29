/*
*
*		qiu_hao		2018/08/27		21:53.pm
*/
#ifndef __CQACTION_H__
#define __CQACTION_H__

#include <tuple>
#include <functional>
#include <type_traits>
#include "CQMacros.h"

NS_CQ_BEGIN

template<size_t...idxs>
struct Index
{

};

template<size_t N, size_t...idxs>
struct SeqGen : SeqGen<N - 1, N - 1, idxs...>
{

};

template<size_t...idxs>
struct SeqGen<0, idxs...> : Index<idxs...>
{

};

class Action
{
	virtual void invoke() = 0;
};

template<typename Fn, typename...Args>
class CQAction : public Action
{
public:
	explicit CQAction(const Fn&& _f, Args&&... _args);

	virtual void invoke();

private:
	template<size_t...Idxs>
	void __run(std::tuple<Args...>& _tp, Index<Idxs...>)
	{
		f_(std::get<Idxs>(_tp)...);
	}
	void __run(std::tuple<Args...>& _tp);

private:
	std::function<Fn> f_;
	std::tuple<Args...> parms_;
};

#include "CQAction.inl"

NS_CQ_END

#endif /* __CQACTION_H__ */