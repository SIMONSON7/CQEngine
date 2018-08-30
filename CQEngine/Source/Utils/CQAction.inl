template <typename R, typename Fn, typename... Args>
inline typename std::enable_if<is_pointer_noref<Fn>::value, R>::type 
__do_call(Fn&& _f, Args&&... _args)
{
	return (*std::forward<Fn>(_f))(std::forward<Args>(_args)...);
}

template <typename R, typename Fn, typename P1, typename... Args>
inline typename std::enable_if<is_memfunc_noref<Fn>::value && is_pointer_noref<P1>::value, R>::type 
__do_call(Fn&& _f, P1&& _this_ptr, Args&&... _args)
{
	return (std::forward<P1>(_this_ptr)->*std::forward<Fn>(_f))(std::forward<Args>(_args)...);
}

template <typename R, typename Fn, typename P1, typename... Args>
inline typename std::enable_if<is_memfunc_noref<Fn>::value && !is_pointer_noref<P1>::value, R>::type 
__do_call(Fn&& _f, P1&& this_obj, Args&&... _args)
{
	return (std::forward<P1>(this_obj).*std::forward<Fn>(_f))(std::forward<Args>(_args)...);
}

template <typename R, typename Fn, typename... Args>
inline typename std::enable_if<!is_pointer_noref<Fn>::value && !is_memfunc_noref<Fn>::value, R>::type 
__do_call(Fn&& _f, Args&&... _args)
{
	return std::forward<Fn>(_f)(std::forward<Args>(_args)...);
}

