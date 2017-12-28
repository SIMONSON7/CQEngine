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
	dbgPrintf("\n [alloc]: \n FILE: %s \n LINE: %d \n", _file, _line);
	return alloc(_size);
}

void DefaultAllocator::free(void *_ptr)
{
	CQASSERT(_ptr)
	::free(_ptr);
}

void DefaultAllocator::free(void *_ptr, const char *_file, size_t _line)
{
	dbgPrintf("\n [free]: \n FILE: %s \n LINE: %d \n", _file, _line);
	free(_ptr);
}

size_t DefaultAllocator::getSize1(void *_ptr)
{
	return map_[_ptr];
}

void DefaultAllocator::setSize1(void *_ptr, const size_t _size1)
{
	map_[_ptr] = _size1;
}



