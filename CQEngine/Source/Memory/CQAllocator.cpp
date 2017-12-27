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
	::free(_ptr);
}

size_t DefaultAllocator::getSize1()
{
	return size1_;
}

void DefaultAllocator::setSize1(const size_t _size1)
{
	size1_ = _size1;
}



