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
	void *ret = alloc(_size);
	dbgPrintf("\n [ALLOC]: \n FILE: %s\n LINE: %d\n PTR: %p\n SIZE: %d BYTE\n", _file, _line, ret, _size);
	return ret;
}

void DefaultAllocator::free(void *_ptr)
{
	CQASSERT(_ptr)
	::free(_ptr);
}

void DefaultAllocator::free(void *_ptr, const char *_file, size_t _line)
{
	dbgPrintf("\n [FREE]: \n FILE: %s\n LINE: %d\n PTR: %p\n", _file, _line,_ptr);
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



