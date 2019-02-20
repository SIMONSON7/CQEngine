#include "CQRenderQueue.h"

USING_NS_CQ;

CQRenderQueue::~CQRenderQueue()
{}

CQRenderQueue::CQRenderQueue()
{}

void CQRenderQueue::pushNormalQueue(CQMeshRenderer* _com)
{
	CQASSERT(_com);
	normalQueue_.push_back(_com);
}

void CQRenderQueue::pushTransQueue(CQMeshRenderer* _com)
{
	CQASSERT(_com);
	transQueue_.push_back(_com);
}

void CQRenderQueue::clearAll()
{
	// reverse order.
	transQueue_.clear();
	normalQueue_.clear();
}