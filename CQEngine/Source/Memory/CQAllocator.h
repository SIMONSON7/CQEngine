/*
*
*		qiu_hao		2017/12/25		04:11.pm
*/
#ifndef __CQALLOCATOR_H__
#define __CQALLOCATOR_H__

#include <stdlib.h>
#include "CQMacros.h"

NS_CQ_BEGIN

class AllocatorI
{
public:
	virtual ~AllocatorI() = 0;

	virtual void* alloc(size_t _size) = 0;

	virtual void free(void *_ptr) = 0;

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

NS_CQ_END

#include "CQAllocator.inl"

#endif /*__CQALLOCATOR_H__*/