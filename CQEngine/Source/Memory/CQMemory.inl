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
T** CQMemory::cvNew2(const size_t _size1, const size_t _size2)
{
	T**		ret = nullptr;
	size_t size = _size1*_size2;
	CQASSERT(size >= 0);

	ret = (T**)CQ_MALLOC(sizeof(T*)*_size1);
	ret[0] = CQ_NEW1(ret[0],T,size);

	for (int i = 0; i < _size1; ++i)
	{
		ret[i] = &ret[0][i*_size2];
	}
	return ret;
}

template <typename T>
T*** CQMemory::cvNew3(const size_t _size1, const size_t _size2, const size_t _size3)
{
	T*** ret = nullptr;
	size_t size12 = _size1*_size2;
	size_t size = size12*_size3;
	CQASSERT(size >= 0);

	ret	= (T***)CQ_MALLOC(sizeof(T**)*_size1);
	ret[0] = (T**)CQ_MALLOC(sizeof(T*)*size12);
	ret[0][0] = CQ_NEW1(ret[0][0],T,size);

	for (int i = 0; i < _size1; ++i)
	{
		ret[i] = &ret[0][i*_size2];
	}
	for (int i = 0;i < size12;++i)
	{
		ret[0][i] = &ret[0][0][i*_size3];
	}
	return ret;
}

template <typename T>
T**** CQMemory::cvNew4(const size_t _size1, const size_t _size2, const size_t _size3,const size_t _size4)
{
	T**** ret = nullptr;
	size_t size12	= _size1*_size2;
	size_t size123	= size12*_size3;
	size_t size		= size123*_size4;
	CQASSERT(size >= 0);

	ret = (T****)CQ_MALLOC(sizeof(T***)*_size1);
	ret[0] = (T***)CQ_MALLOC(sizeof(T**)*size12);
	ret[0][0] = (T**)CQ_MALLOC(sizeof(T*)*size123);
	ret[0][0][0] = CQ_NEW1(ret[0][0][0], T, size);

	for (int i = 0 ; i < _size1; ++i)
	{
		ret[i] = &ret[0][i*_size2];
	}
	for (int i = 0; i < size12; ++i)
	{
		ret[0][i] = &ret[0][0][i*_size3];
	}
	for (int i = 0 ; i < size123; ++i)
	{
		ret[0][0][i] = &ret[0][0][0][i*_size4];
	}
	return ret;
}

template <typename T>
void CQMemory::cvDelete2(T** _ptr)
{
	CQASSERT((_ptr) && (_ptr[0]));
	CQ_DELETE1(_ptr[0],T);
	CQ_FREE(_ptr);
}

template <typename T>
void CQMemory::cvDelete3(T*** _ptr)
{
	CQASSERT((_ptr) && (_ptr[0]) &&(_ptr[0][0]));
	CQ_DELETE1(_ptr[0][0],T);
	CQ_FREE(_ptr[0]);
	CQ_FREE(_ptr);
}

template <typename T>
void CQMemory::cvDelete4(T**** _ptr)
{
	CQASSERT((_ptr) && (_ptr[0]) && (_ptr[0][0]) && (_ptr[0][0][0]));
	CQ_DELETE1(_ptr[0][0][0],T);
	CQ_FREE(_ptr[0][0]);
	CQ_FREE(_ptr[0]);
	CQ_FREE(_ptr);
}
