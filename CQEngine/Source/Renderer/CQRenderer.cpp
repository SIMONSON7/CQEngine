#include "CQMemory.h"
#include "CQWglContext.h"
#include "CQObject.h"
#include "CQMeshRenderer.h"
#include "CQRenderQueue.h"
#include "CQRenderer.h"

USING_NS_CQ

CQRenderer::CQRenderer()
{
#if defined(_MSC_VER)
	CQWglContext* wc = CQ_NEW(CQWglContext);
	context_ = dynamic_cast<CQContext*>(wc);
#else
#endif

	renderQueue_ = CQ_NEW(CQRenderQueue);
}

CQRenderer:: ~CQRenderer()
{
	if (context_ != nullptr)
	{
#if defined(_MSC_VER)
		CQWglContext* wc = static_cast<CQWglContext*>(context_);
		CQASSERT(wc);
		wc->destroyRenderContext();
		CQ_DELETE(wc, CQWglContext);
		context_ = nullptr;
#else
#endif
	}

	CQ_DELETE(renderQueue_, CQRenderQueue);
}

CQContext * CQRenderer::getContext()
{
	return context_;
}

void CQRenderer::draw(std::vector<CQObject*> _visibleObjs)
{
	for each (auto obj in _visibleObjs)
	{
		//auto type = obj->getMaterial().type();
		//switch (type)
		//{
		//case normal:
		auto meshRender = std::dynamic_pointer_cast<CQMeshRenderer>
			(obj->getComponentByName("MeshRender")).get();
		if (meshRender)
		{
			renderQueue_->pushNormalQueue(meshRender);
		}
		//	break;
		//default:
		//	break;
		//}
	}

	for each (auto meshRender in renderQueue_->normalQueue_)
	{
		__drawNormal(meshRender);
	}

	for each (auto meshRender in renderQueue_->transQueue_)
	{
		__drawTransparent(meshRender);
	}
}

void CQRenderer::__drawNormal(CQMeshRenderer * _meshRender)
{
	CQASSERT(_meshRender);





}

void CQRenderer::__drawTransparent(CQMeshRenderer * _meshRender)
{

}

