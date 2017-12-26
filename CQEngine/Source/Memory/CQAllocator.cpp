#include "CQAllocator.h"

USING_NS_CQ

DefaultAllocator::DefaultAllocator() {}

DefaultAllocator::~DefaultAllocator() {}


void* DefaultAllocator::alloc(size_t _size)
{
	return malloc(_size);
}

void DefaultAllocator::free(void *_ptr)
{
	CQASSERT(_ptr)
	free(_ptr);
}




