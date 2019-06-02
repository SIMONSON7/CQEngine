#include "SkyBoxScene.h"

//REGISTER_START_SCENE(SkyBoxScene)

void SkyBoxScene::onInit()
{
	dbgPuts("[SkyBoxScene] init success!");

	// camera
	// TODO : should have a default camera.
	camera_ = CQ_NEW(CQCamera);

	// Evt
	CQEvtDispatcher* dispatcher = CQCore::shareCore()->shareEvtDispatcher();

	clickListener_ = std::make_shared<CQEvtListener>();
	clickListener_->setEvtID(CQInput::EvtID::MOUSE_L_CLICK_BEGIN);
	clickListener_->setCB(std::bind(&SkyBoxScene::onMouseClick, this, std::placeholders::_1));

	wheelListener_ = std::make_shared<CQEvtListener>();
	wheelListener_->setEvtID(CQInput::EvtID::MOUSE_WHEEL);
	wheelListener_->setCB(std::bind(&SkyBoxScene::onMouseWheel, this, std::placeholders::_1));

	dispatcher->registerListener(clickListener_);
	dispatcher->registerListener(wheelListener_);

	// Bunny
	CQObject * bunnyObj = CQ_NEW(CQObject);
	bunnyObj->setName("bunnyObj");
	bunnyNode_ = CQ_NEW(CQSceneNode, CQSceneNode::s_root_, bunnyObj, "bunny");

	// mesh
	auto bunnyMesh = std::dynamic_pointer_cast<CQMesh>(CQCore::shareCore()->shareResManager()->getRes(VNAME(ResIDDef::BUNNY_MESH)));

	// shader 
	auto program = CQ_NEW(CQShaderProgram);
	// TMP
	/*auto vs = std::dynamic_pointer_cast<CQShader>(CQCore::shareCore()->shareResManager()->getRes(VNAME(ResIDDef::DEF_VERTEX_SHADER)));
	auto fs = std::dynamic_pointer_cast<CQShader>(CQCore::shareCore()->shareResManager()->getRes(VNAME(ResIDDef::DEF_NO_TEX_FRAGMENT_SHADER)));*/
	auto vs = std::dynamic_pointer_cast<CQShader>(CQCore::shareCore()->shareResManager()->getRes(VNAME(ResIDDef::DEF_DIFFUSE_VERTEX_SHADER)));
	auto fs = std::dynamic_pointer_cast<CQShader>(CQCore::shareCore()->shareResManager()->getRes(VNAME(ResIDDef::DEF_DIFFUSE_FRAGMENT_SHADER)));
	program->attachNativeShader((const char *)(vs->getRawData()->data_), ShaderType::VERTEX);
	program->attachNativeShader((const char *)(fs->getRawData()->data_), ShaderType::PIXEL);
	program->genProgram();

	// material
	auto material = CQ_NEW(CQMaterial);
	material->setProgram(program);
	auto materials = CQ_NEW(std::vector<CQMaterial*>);
	materials->push_back(material);

	// meshRender
	auto bunnyMR = std::make_shared<CQMeshRenderer>();
	bunnyMR->setup(bunnyMesh.get(), nullptr, materials);

	bunnyObj->setComponent(std::dynamic_pointer_cast<CQComponent>(bunnyMR));

	// bunny transform
	bunnyObj->getTransform()->setScale(0.8f);
	bunnyObj->getTransform()->moveTo(Vector3(0, -0.5f, -1.5f));
}

void SkyBoxScene::update()
{
	// program
	auto mr = std::dynamic_pointer_cast<CQMeshRenderer>(bunnyNode_->getObj()->getComponentByName("MeshRender"));
	auto program = (*mr->getMaterials())[0]->getProgram();
	program->load();

	// bunny transform
	auto bunnyTrans = bunnyNode_->getObj()->getTransform();
	bunnyTrans->rot(++modelAngle_, bunnyTrans->getUp()); // rot self axis.
	Matrix4 modelMat = bunnyTrans->getModelMat();

	// camera transform
	auto transform = camera_->getTransform();
	transform->buildLocalCoordinate(Vector3(0, 0, camRadisZ_), Vector3(0, 0, 0), Vector3(0, 1, 0));
	float aspect(800.0f / 600.0f);
	auto viewMat = transform->calWorldToLcalMatRH();
	auto projMat = camera_->calPerspectiveMat(60, aspect, 0.1f, 100.0f);

	// TODO:
	// user should NOT manipulate mvp Matrix.
	Matrix4 mvp = projMat * viewMat * modelMat;
	// TMP
	//program->setMatrix("mvp", mvp);
	Matrix4 mv = viewMat * modelMat;

	program->setVector("uLightPosEyeSpace", viewMat * Vector4(10.0f, 10.0f, 10.0f, 1.0f));
	program->setVector("uKd", Vector3(0.9f, 0.5f, 0.3f));
	program->setVector("uLd", Vector3(1.0f, 1.0f, 1.0f));

	program->setMatrix("uModelViewMatrix", mv);
	program->setMatrix("uMVP", mvp);
	program->setMatrix("uNormalMatrix", Matrix3(Vector3(mv[0].x, mv[0].y, mv[0].z), 
												Vector3(mv[1].x, mv[1].y, mv[1].z), 
												Vector3(mv[2].x, mv[2].y, mv[2].z)));


}

void SkyBoxScene::onMouseClick(void* _clickData)
{
	if (_clickData)
	{
		CQInput::MouseEvt *evt = static_cast<CQInput::MouseEvt*>(_clickData);
		if (evt && evt->id_ == CQEngine::CQInput::MOUSE_L_CLICK_BEGIN)
		{
			dbgPrintf("[SkyBoxScene] click x : %d", evt->x_);
		}
	}
}

void SkyBoxScene::onMouseWheel(void* _wheelData)
{
	if (_wheelData)
	{
		CQInput::MouseEvt *evt = static_cast<CQInput::MouseEvt*>(_wheelData);
		if (evt && evt->id_ == CQEngine::CQInput::MOUSE_WHEEL)
		{
			dbgPrintf("[SkyBoxScene] wheel delta : %d", evt->delta_);

			if (evt->delta_ > 0)
			{
				camRadisZ_ *= 1.2f;
			}

			if (evt->delta_ < 0)
			{
				camRadisZ_ *= 0.8f;
			}
		}
	}
}

void SkyBoxScene::onDestory()
{
	CQ_DELETE(camera_, CQCamera);

	CQCore::shareCore()->shareEvtDispatcher()->unregisterListener(clickListener_);
	CQCore::shareCore()->shareEvtDispatcher()->unregisterListener(wheelListener_);
}