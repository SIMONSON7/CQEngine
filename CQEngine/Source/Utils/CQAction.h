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

// sequence generator for std::tuple
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

// for uppacking parameter
template <typename T>
inline auto g_select(T&& val)->T&&
{
	return std::forward<T>(val);
}

// result type traits 
template <typename Fn>
struct result_traits : result_traits<decltype(&Fn::operator())> {};

template <typename T>
struct result_traits<T*> : result_traits<T> {};

template <typename R, typename... Args>
struct result_traits<R(*)(Args...)> { typedef R type; };

#define RESULT_TRAITS__(...) \
    template <typename R, typename C, typename... Args> \
    struct result_traits<R(C::*)(Args...) __VA_ARGS__> { typedef R type; };

RESULT_TRAITS__()
RESULT_TRAITS__(const)
RESULT_TRAITS__(volatile)
RESULT_TRAITS__(const volatile)

#undef RESULT_TRAITS__

// pointer traits
template <typename T>
struct is_memfunc_noref
	: std::is_member_function_pointer<typename std::remove_reference<T>::type>
{

};

template <typename T>
struct is_pointer_noref
	: std::is_pointer<typename std::remove_reference<T>::type>
{

};

//-------------------------------------------------------------------------//
class Action
{
public:
	virtual void invoke() {};
};

template<typename Fn, typename...Args>
class CQAction : public Action
{
private:
	typedef typename std::decay<Fn>::type				call_type;
	typedef typename result_traits<call_type>::type     result_type;

public:
	explicit CQAction(Fn&& _f, Args&&... _args)
		:
		f_(std::forward<Fn>(_f)),
		parms_(std::forward<Args>(_args)...) 
	{
	
	}

	virtual void invoke()
	{
		return __call(parms_);
	}

private:
	void __call(std::tuple<Args...>& _tp)
	{
		__call(_tp, SeqGen<sizeof...(Args)>());
	}

	template<size_t...Idxs>
	auto __call(std::tuple<Args...>& _tp, Index<Idxs...>)
	{
		return __do_call<result_type>(f_, g_select(std::get<Idxs>(_tp))...);
	}

private:
	call_type f_;
	std::tuple<Args...> parms_;
};

#include "CQAction.inl"

NS_CQ_END

#endif /* __CQACTION_H__ */