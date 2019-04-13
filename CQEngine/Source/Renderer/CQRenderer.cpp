#include <glad/glad.h>
#include "CQMemory.h"
#include "CQDebug.h"
#include "CQWglContext.h"
#include "CQObject.h"
#include "CQTexture.h"
#include "CQShader.h"
#include "CQShaderProgram.h"
#include "CQMesh.h"
#include "CQMaterial.h"
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
	// TODO:
	// render state should call once.
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	renderQueue_->clearAll();
}

void CQRenderer::__drawNormal(CQMeshRenderer * _meshRender)
{
	CQASSERT(_meshRender);

	// TODO:
	// * glClear should no be here.
	// * sharedMesh()[0]
	auto handles = _meshRender->getSubMeshHandles();
	auto mesh = _meshRender->getMesh()->sharedMesh()[0];
	auto mat = (*_meshRender->getMaterials())[0];
	auto program = mat->getProgram();

	program->load();

	//// draw elements
	CQ_GLCHECK(glBindVertexArray(handles[0]));
	{
		CQ_GLCHECK(glDrawElements(GL_TRIANGLES, mesh->iBuff_.size(), GL_UNSIGNED_INT, 0));
	}
	CQ_GLCHECK(glBindVertexArray(0));

}

void CQRenderer::__drawTransparent(CQMeshRenderer * _meshRender)
{

}

