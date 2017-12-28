#include "CQAllocator.h"
#include "CQDebug.h"

USING_NS_CQ

DefaultAllocator::DefaultAllocator() {}

DefaultAllocator::~DefaultAllocator() {}

void* DefaultAllocator::alloc(size_t _size)
{
	return malloc(_size);
}

void* DefaultAllocator::alloc(size_t _size, const char *_file, size_t _line)
{
#ifdef CQDEBUG
	dbgPrintf("\n [alloc]: \n FILE: %s \n LINE: %d \n", _file, _line);
#endif
	return alloc(_size);
}

void DefaultAllocator::free(void *_ptr)
{
	CQASSERT(_ptr)
	::free(_ptr);
}

void DefaultAllocator::free(void *_ptr, const char *_file, size_t _line)
{
#ifdef CQDEBUG
	dbgPrintf("\n [free]: \n FILE: %s \n LINE: %d \n", _file, _line);
#endif
	free(_ptr);
}

size_t DefaultAllocator::getSize1()
{
	return size1_;
}

void DefaultAllocator::setSize1(const size_t _size1)
{
	size1_ = _size1;
}



