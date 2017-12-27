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

//template <typename T>
//T* Memory::New1(const size_t _size1,...)
//{
//	T *ptr = (T*)g_allocator->alloc(_size1);
//	T* obj = ptr;
//	for (int i = 0 ; i < _size1; ++i ,++obj)
//	{
//		// "..." CANNOT transmit //
//		obj = ::new(CQEngine::CQPlacemenNewTag(), CQEngine::Memory::g_allocator->alloc(sizeof(T))) T(...);
//	}
//
//	return ptr;
//}