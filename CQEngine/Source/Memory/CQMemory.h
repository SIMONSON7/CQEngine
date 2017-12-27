/*
*
*		qiu_hao		2017/12/26		05:44.pm
*/
#ifndef __CQMEMORY_H__
#define __CQMEMORY_H__

#include <new>
#include <stdarg.h>
#include "CQAllocator.h"

NS_CQ_BEGIN

class Memory
{
public:
	static AllocatorI *g_allocator;
public:
};


NS_CQ_END

//----------------------------------------------------------------------------
namespace CQEngine { struct CQPlacemenNewTag {}; } // For placement new
inline void* operator new(size_t, CQEngine::CQPlacemenNewTag, void *_ptr);
inline void operator delete(void *, CQEngine::CQPlacemenNewTag, void *_ptr) throw();

#define CQ_RAW_NEW(_type,...)				::new _type(##__VA_ARGS__);
#define CQ_RAW_DELETE(_ptr)					do{ if(_ptr){::delete _ptr;_ptr=nullptr;} }while(0)
#define CQ_NEW0(_type,...)					CQ_NEW(_type,##__VA_ARGS__)
#define CQ_NEW(_type,...)					CQ_PLACEMENT_NEW(CQEngine::Memory::g_allocator->alloc(sizeof(_type)),_type,##__VA_ARGS__)
#define CQ_DELETE(_ptr)						CQ_RAW_DELETE(_ptr)
#define CQ_NEW1(_ptr,_type,_size1,...)	\
	_ptr = (_type*)CQEngine::Memory::g_allocator->alloc(_size1); \
	_type* obj = _ptr; \
	for (int i = 0 ; i < _size1; ++i ,++obj) \
	{ \
		obj = CQ_NEW0(_type,##__VA_ARGS__) ; \
	} \

#define CQ_PLACEMENT_NEW(_ptr,_type,...)	::new(CQEngine::CQPlacemenNewTag(),_ptr) _type(__VA_ARGS__);
 

#include "CQMemory.inl"

#endif /*__CQMEMORY_H__*/

