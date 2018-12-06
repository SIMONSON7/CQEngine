#include "CQMemory.h"
#include "CQWglContext.h"
#include "CQRenderer.h"

USING_NS_CQ

CQRenderer::CQRenderer()
{
#if defined(_MSC_VER)
	CQWglContext* wc = CQ_NEW(CQWglContext);
	context_ = dynamic_cast<CQContext*>(wc);
#else
#endif
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
}

CQContext * CQRenderer::getContext()
{
	return context_;
}

void CQRenderer::draw(std::vector<CQVisiableObj *> _visibleObjVec)
{

}

