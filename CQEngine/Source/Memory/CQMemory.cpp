#include "CQMemory.h"

USING_NS_CQ

// TMP //
AllocatorI *Memory::g_allocator = new DefaultAllocator();