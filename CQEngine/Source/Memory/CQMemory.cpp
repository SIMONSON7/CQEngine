#include "CQMemory.h"

USING_NS_CQ

AllocatorI *Memory::g_allocator = new DefaultAllocator();