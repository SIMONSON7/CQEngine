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




	return nullptr;
}

template <typename T>
void Memory::cvDelete2(T** _ptr)
{

}
