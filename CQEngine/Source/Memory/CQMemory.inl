/*
*
*		qiu_hao		2017/12/26		03:20.pm
*/

inline void* operator new(size_t, CQEngine::CQPlacemenNewTag, void *_ptr)
{
	return _ptr;
}

inline void operator delete(void *, CQEngine::CQPlacemenNewTag, void *_ptr) throw()
{
	CQASSERT(false);
}

template <typename T>
T** Memory::cvNew2(const size_t _size1, const size_t _size2)
{
	T**		ret = nullptr;
	size_t size = _size1*_size2;
	CQASSERT(size >= 0);

	ret = (T**)CQ_MALLOC(sizeof(T*)*_size1);
	ret[0] = (T*)CQ_NEW1(ret[0],T,size);

	for (int i = 0; i < _size1; ++i)
	{
		ret[i] = &ret[0][i*_size2];
	}

	return ret;
}

template <typename T>
void Memory::cvDelete2(T** _ptr)
{
	CQASSERT((_ptr) && (_ptr[0]));
	CQ_DELETE1(_ptr[0],T);
	CQ_FREE(_ptr);
}
