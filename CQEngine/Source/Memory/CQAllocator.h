/*
*
*		qiu_hao		2017/12/25		04:11.pm
*/
#ifndef __CQALLOCATOR_H__
#define __CQALLOCATOR_H__

#include <new>
#include "CQMacros.h"

NS_CQ_BEGIN

class AllocatorI
{
public:
	virtual ~AllocatorI() = 0;
};

class DefaultAllocator : public AllocatorI
{
public:
	DefaultAllocator();

	virtual ~DefaultAllocator();
public:
	void* alloc(size_t _size);

	void free(void *_ptr);

};

static AllocatorI* g_allocator = nullptr;

//----------------------------------------------------------------------------

struct CQPlacemenNewTag {}; // For placement new
inline void* operator new(size_t, CQEngine::CQPlacemenNewTag, void *_ptr);
inline void operator delete(void *, CQEngine::CQPlacemenNewTag, void *_ptr) throw();










#include "CQAllocator.inl"

NS_CQ_END

#endif /*__CQALLOCATOR_H__*/