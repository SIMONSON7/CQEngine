#include "CQMemory.h"

USING_NS_CQ

// TMP //
AllocatorI *CQMemory::g_allocator = CQ_RAW_NEW0(DefaultAllocator);