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

	virtual size_t getSize1() = 0;

	virtual void setSize1(const size_t _size1) = 0;

};

class DefaultAllocator : public AllocatorI
{
public:
	DefaultAllocator();

	virtual ~DefaultAllocator();

public:
	void* alloc(size_t _size);

	void free(void *_ptr);

public:
	size_t getSize1();

	void setSize1(const size_t _size1);

private:
	size_t size1_;

};

NS_CQ_END

#include "CQAllocator.inl"

#endif /*__CQALLOCATOR_H__*/