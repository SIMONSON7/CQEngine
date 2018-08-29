template<typename Fn, typename...Args>
CQAction<Fn, Args...>::CQAction(const Fn&& _f, Args&&... _args)
{
	f_ = std::forward<Fn>(_f);
	parms_ = std::tuple<std::decay_t<Args>...>(std::forward<Args>(_args)...);
}

template<typename Fn, typename...Args>
void CQAction<Fn, Args...>::invoke()
{
	__run(parms_);
}

template<typename Fn, typename...Args>
void CQAction<Fn, Args...>::__run(std::tuple<Args...>& _tp)
{
	//cout << sizeof...(Args) << endl;
	//auto a = SeqGen<sizeof...(Args)>();
	__run(_tp, SeqGen<sizeof...(Args)>());
}

