#include "CQMemory.h"

USING_NS_CQ

static AllocatorI *s_allocator = nullptr;

AllocatorI* CQMemory::shareAllocator()
{
	if (!s_allocator)
	{
		s_allocator = CQ_RAW_NEW(DefaultAllocator);
	}
	return s_allocator;
}

void CQMemory::releaseAllocator()
{
	CQ_RAW_DELETE(s_allocator);
}