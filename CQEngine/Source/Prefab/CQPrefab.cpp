#include "CQMemory.h"
#include "CQMeshRenderer.h"
#include "CQSceneNode.h"
#include "CQPrefab.h"

USING_NS_CQ;

CQPrefab::CQPrefab()
{
	CQObject * obj = CQ_NEW(CQObject);
	obj->setName("Prefab_Obj");
	node_ = CQ_NEW(CQSceneNode, CQSceneNode::s_root_, obj, "Prefab_Node");

	auto mr = std::make_shared<CQMeshRenderer>();
	obj->setComponent(std::dynamic_pointer_cast<CQComponent>(mr));
}

CQPrefab::~CQPrefab()
{
	CQ_DELETE(node_, CQSceneNode);
}

void CQPrefab::setupSurface(CQMaterial * _mat, CQLight * _light)
{
	if (_mat)
	{
		auto mr = std::dynamic_pointer_cast<CQMeshRenderer>(node_->getObj()->getComponentByName("MeshRender"));
		if (mr)
		{
			auto materials = CQ_RAW_NEW(std::vector<CQMaterial*>);
			materials->push_back(_mat);
			
			mr->setSurfaceData(materials, _light);
		}
	}
}