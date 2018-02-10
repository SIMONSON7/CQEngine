#include "CQMemory.h"

USING_NS_CQ

AllocatorI* CQMemory::shareAllocator()
{
	// Not use dynamic alloc for s_allocator,
	// then we No need to worry the dtor of s_allocator.
	// "static" can guarantee the singleton of DefaultAllocator.
	static DefaultAllocator s_allocator;
	return &s_allocator;
}
