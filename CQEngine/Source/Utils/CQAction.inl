template <typename R, typename Fn, typename... Args>
inline typename std::enable_if<is_pointer_noref<Fn>::value, R>::type
__do_call(Fn&& _f, Args&&... _args)
{
	return (*std::forward<Fn>(_f))(std::forward<Args>(_args)...);
}

template <typename R, typename Fn, typename THIS, typename... Args>
inline typename std::enable_if<is_memfunc_noref<Fn>::value && is_pointer_noref<THIS>::value, R>::type
__do_call(Fn&& _f, THIS&& _this, Args&&... _args)
{
	return (std::forward<THIS>(_this)->*std::forward<Fn>(_f))(std::forward<Args>(_args)...);
}

template <typename R, typename Fn, typename THIS, typename... Args>
inline typename std::enable_if<is_memfunc_noref<Fn>::value && !is_pointer_noref<THIS>::value, R>::type
__do_call(Fn&& _f, THIS&& this_obj, Args&&... _args)
{
	return (std::forward<THIS>(this_obj).*std::forward<Fn>(_f))(std::forward<Args>(_args)...);
}

template <typename R, typename Fn, typename... Args>
inline typename std::enable_if<!is_pointer_noref<Fn>::value && !is_memfunc_noref<Fn>::value, R>::type
__do_call(Fn&& _f, Args&&... _args)
{
	return std::forward<Fn>(_f)(std::forward<Args>(_args)...);
}

