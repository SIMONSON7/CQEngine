#include "CQMemory.h"
#include "CQMeshRenderer.h"
#include "CQSceneNode.h"
#include "CQPrefab.h"

USING_NS_CQ;

CQPrefab::CQPrefab()
{
	CQObject * obj = CQ_NEW(CQObject);
	node_ = CQ_NEW(CQSceneNode, CQSceneNode::s_root_, obj, "Prefab");

	auto mr = std::make_shared<CQMeshRenderer>();
	obj->setComponent(std::dynamic_pointer_cast<CQComponent>(mr));
}

CQPrefab::~CQPrefab()
{
	CQ_DELETE(node_, CQSceneNode);
}

void CQPrefab::setupSurface(CQMaterial * _mat)
{

}