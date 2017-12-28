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
