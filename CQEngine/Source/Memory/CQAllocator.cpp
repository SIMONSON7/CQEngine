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
	CQASSERT(_ptr);
	CQASSERT(&map_[_ptr]);
	return map_[_ptr].size_[0];
}

size_t DefaultAllocator::getSize2(void *_ptr)
{
	CQASSERT(_ptr);
	CQASSERT(&map_[_ptr]);
	return map_[_ptr].size_[1];
}

size_t DefaultAllocator::getSize3(void *_ptr)
{
	CQASSERT(_ptr);
	CQASSERT(&map_[_ptr]);
	return map_[_ptr].size_[2];
}

size_t DefaultAllocator::getSize4(void *_ptr)
{
	CQASSERT(_ptr);
	CQASSERT(&map_[_ptr]);
	return map_[_ptr].size_[3];
}

void DefaultAllocator::setSize1(void *_ptr, const size_t _size1)
{
	CQASSERT(_ptr && (_size1 >= 0));
	Info info;
	info.size_[0] = _size1;
	map_[_ptr] = info;
}

void DefaultAllocator::setSize2(void *_ptr, const size_t _size2)
{
	CQASSERT(_ptr && (_size2 >= 0));
	CQASSERT(&map_[_ptr]);
	map_[_ptr].size_[1] = _size2;
}

void DefaultAllocator::setSize3(void *_ptr, const size_t _size3)
{
	CQASSERT(_ptr && (_size3 >= 0));
	CQASSERT(&map_[_ptr]);
	map_[_ptr].size_[2] = _size3;
}

void DefaultAllocator::setSize4(void *_ptr, const size_t _size4)
{
	CQASSERT(_ptr && (_size4 >= 0));
	CQASSERT(&map_[_ptr]);
	map_[_ptr].size_[3] = _size4;
}












