#include "CQMemory.h"

USING_NS_CQ

AllocatorI* CQMemory::shareAllocator()
{
	static DefaultAllocator s_allocator;
	return &s_allocator;
}
