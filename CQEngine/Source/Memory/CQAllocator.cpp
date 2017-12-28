#include "CQAllocator.h"
#include "CQDebug.h"

USING_NS_CQ

DefaultAllocator::DefaultAllocator() {}

DefaultAllocator::~DefaultAllocator() {}


void* DefaultAllocator::alloc(size_t _size)
{
#ifdef CQDEBUG
	dbgPrintf("\n [alloc]: \n FILE: %s \n LINE: %d \n", __FILE__, __LINE__);
#endif
	return malloc(_size);
}

void DefaultAllocator::free(void *_ptr)
{
#ifdef CQDEBUG
	dbgPrintf("\n [free]: \n FILE: %s \n LINE: %d \n", __FILE__, __LINE__);
#endif
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



