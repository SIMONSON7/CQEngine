/*
*
*		qiu_hao		2017/12/26		05:44.pm
*/
#ifndef __CQMEMORY_H__
#define __CQMEMORY_H__

#include <new>
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

#define DEFAULT_ALLOCATOR CQEngine::Memory::g_allocator
#define DEFAULT_ALLOCATOR_SETSIZE1(_ptr,_size1) DEFAULT_ALLOCATOR->setSize1(_ptr,_size1) 
#define DEFAULT_ALLOCATOR_GETSIZE1(_ptr) DEFAULT_ALLOCATOR->getSize1(_ptr)
#ifdef CQDEBUG
#define DEFAULT_ALLOCATOR_ALLOC(_size1) DEFAULT_ALLOCATOR->alloc(_size1,__FILE__,__LINE__)
#define DEFAULT_ALLOCATOR_FREE(_ptr) DEFAULT_ALLOCATOR->free(_ptr,__FILE__,__LINE__)
#elif
#define DEFAULT_ALLOCATOR_ALLOC(_size1) DEFAULT_ALLOCATOR->alloc(_size1)
#define DEFAULT_ALLOCATOR_FREE(_ptr) DEFAULT_ALLOCATOR->free(_ptr)
#endif

#define CQ_NEW(_type,...)					CQ_PLACEMENT_NEW(DEFAULT_ALLOCATOR_ALLOC(sizeof(_type)),_type,##__VA_ARGS__)
#define CQ_NEW0(_type,...)					CQ_NEW(_type,##__VA_ARGS__)
#define CQ_NEW1(_ptr,_type,_size1,...)	\
	_ptr = (_type*)DEFAULT_ALLOCATOR_ALLOC(_size1*sizeof(_type)); \
	{ \
		_type *obj = _ptr; \
		for (int i = 0 ; i < _size1; ++i ,++obj) \
		{ \
			CQ_PLACEMENT_NEW(obj,_type,##__VA_ARGS__); \
		} \
		DEFAULT_ALLOCATOR_SETSIZE1(_ptr,_size1);\
	} \

#define CQ_RAW_NEW(_type,...)				::new _type(##__VA_ARGS__);
#define CQ_RAW_NEW0(_type,...)				CQ_RAW_NEW(_type,##__VA_ARGS__);
#define CQ_RAW_NEW1(_type,_size)			::new _type[_size];
#define CQ_PLACEMENT_NEW(_ptr,_type,...)	::new(CQEngine::CQPlacemenNewTag(),_ptr) _type(__VA_ARGS__);

#define CQ_DELETE(_ptr,_type)	\
	if(_ptr) \
	{ \
		_ptr->~_type(); \
		DEFAULT_ALLOCATOR_FREE(_ptr); \
		_ptr = nullptr; \
	} \

#define CQ_DELETE0(_ptr,_type)					CQ_DELETE(_ptr,_type)
#define CQ_DELETE1(_ptr,_type) \
	if(_ptr) \
	{\
		size_t size = DEFAULT_ALLOCATOR_GETSIZE1(_ptr);\
		_type *obj = _ptr; \
		for(int i = 0; i < size; ++i ,++obj ) \
		{\
			obj->~_type(); \
		}\
		DEFAULT_ALLOCATOR_FREE(_ptr); \
		_ptr = nullptr; \
	}\

#define CQ_RAW_DELETE(_ptr)					do{ if(_ptr){::delete _ptr;_ptr=nullptr;} }while(0) 
#define CQ_RAW_DELETE0(_ptr)				CQ_RAW_DELETE(_ptr)
#define CQ_RAW_DELETE1(_ptr)				do{ if(_ptr){::delete[] _ptr;_ptr=nullptr;} }while(0) 

namespace CQEngine { struct CQPlacemenNewTag {}; } // For placement new
inline void* operator new(size_t, CQEngine::CQPlacemenNewTag, void *_ptr);
inline void operator delete(void *, CQEngine::CQPlacemenNewTag, void *_ptr) throw();

#include "CQMemory.inl"

#endif /*__CQMEMORY_H__*/

