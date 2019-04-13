#include "LightExScene.h"

//REGISTER_START_SCENE(LightExScene)

void LightExScene::onInit()
{
	dbgPuts("[LightExScene] init success!");

	// camera
	// TODO : should have a default camera.
	camera_ = CQ_NEW(CQCamera);

	// Evt
	CQEvtDispatcher* dispatcher = CQCore::shareCore()->shareEvtDispatcher();

	clickListener_ = std::make_shared<CQEvtListener>();
	clickListener_->setEvtID(CQInput::EvtID::MOUSE_L_CLICK_BEGIN);
	clickListener_->setCB(std::bind(&LightExScene::onMouseClick, this, std::placeholders::_1));

	wheelListener_ = std::make_shared<CQEvtListener>();
	wheelListener_->setEvtID(CQInput::EvtID::MOUSE_WHEEL);
	wheelListener_->setCB(std::bind(&LightExScene::onMouseWheel, this, std::placeholders::_1));

	dispatcher->registerListener(clickListener_);
	dispatcher->registerListener(wheelListener_);

	// Bunny
	CQObject * bunnyObj = CQ_NEW(CQObject);
	bunnyObj->setName("bunnyObj");
	bunnyNode_ = CQ_NEW(CQSceneNode, CQSceneNode::s_root_, bunnyObj, "bunny");

	// mesh
	auto bunnyMesh = std::dynamic_pointer_cast<CQMesh>(CQCore::shareCore()->shareResManager()->getRes(VNAME(ResIDDef::BUNNY_MESH)));

	// light
	lights_[0].setWorldPos(Vector4(10.0f, 10.0f, 10.0f, 1.0f));
	lights_[1].setWorldPos(Vector4(20.0f, -10.0f, 10.0f, 1.0f));
	lights_[2].setWorldPos(Vector4(10.0f, 20.0f, -10.0f, 1.0f));
	lights_[3].setWorldPos(Vector4(10.0f, -10.0f, 20.0f, 1.0f));
	lights_[4].setWorldPos(Vector4(-10.0f, 10.0f, 10.0f, 1.0f));

	lights_[0].setColor(Vector3(0.0f, 1.0f, 1.0f));
	lights_[1].setColor(Vector3(0.0f, 0.0f, 1.0f));
	lights_[2].setColor(Vector3(1.0f, 0.0f, 0.0f));
	lights_[3].setColor(Vector3(0.0f, 0.8f, 0.0f));
	lights_[4].setColor(Vector3(1.0f, 1.0f, 0.0f));

	// shader 
	auto mLightProgram = CQ_NEW(CQShaderProgram);
	auto vs = std::dynamic_pointer_cast<CQShader>(CQCore::shareCore()->shareResManager()->getRes(VNAME(ResIDDef::DEF_MULTILIGHT_VERTEX_SHADER)));
	auto fs = std::dynamic_pointer_cast<CQShader>(CQCore::shareCore()->shareResManager()->getRes(VNAME(ResIDDef::DEF_MULTILIGHT_FRAGMENT_SHADER)));
	mLightProgram->attachNativeShader((const char *)(vs->getRawData()->data_), ShaderType::VERTEX);
	mLightProgram->attachNativeShader((const char *)(fs->getRawData()->data_), ShaderType::PIXEL);
	mLightProgram->genProgram();

	// material
	auto material = CQ_NEW(CQMaterial);
	material->setProgram(mLightProgram);
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

void LightExScene::update()
{
	// mLightProgram
	auto mr = std::dynamic_pointer_cast<CQMeshRenderer>(bunnyNode_->getObj()->getComponentByName("MeshRender"));
	auto mLightProgram = (*mr->getMaterials())[0]->getProgram();
	mLightProgram->load();

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
	Matrix4 mv = viewMat * modelMat;

	// TODO
	// light pos : embed to class CQLight.
	for (int i = 0 ; i < 5; ++i)
	{
		mLightProgram->setVector("uLights[0].colorIntensity", lights_[i].getColor());
		mLightProgram->setVector("uLights[0].pos", viewMat * lights_[i].getWorldPos());
	}

	mLightProgram->setVector("uMat.a", Vector3(0.4f, 0.4f, 0.4f));
	mLightProgram->setVector("uMat.d", Vector3(0.9f, 0.9f, 0.9f));
	mLightProgram->setVector("uMat.s", Vector3(0.1f, 0.1f, 0.1f));
	mLightProgram->setFloat("uMat.shineFactor", 110.0f);

	mLightProgram->setMatrix("uModelViewMatrix", mv);
	mLightProgram->setMatrix("uMVP", mvp);
	mLightProgram->setMatrix("uNormalMatrix", Matrix3(Vector3(mv[0].x, mv[0].y, mv[0].z),
		Vector3(mv[1].x, mv[1].y, mv[1].z),
		Vector3(mv[2].x, mv[2].y, mv[2].z)));


}

void LightExScene::onMouseClick(void* _clickData)
{
	if (_clickData)
	{
		CQInput::MouseEvt *evt = static_cast<CQInput::MouseEvt*>(_clickData);
		if (evt && evt->id_ == CQEngine::CQInput::MOUSE_L_CLICK_BEGIN)
		{
			dbgPrintf("[LightExScene] click x : %d", evt->x_);
		}
	}
}

void LightExScene::onMouseWheel(void* _wheelData)
{
	if (_wheelData)
	{
		CQInput::MouseEvt *evt = static_cast<CQInput::MouseEvt*>(_wheelData);
		if (evt && evt->id_ == CQEngine::CQInput::MOUSE_WHEEL)
		{
			dbgPrintf("[LightExScene] wheel delta : %d", evt->delta_);

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

void LightExScene::onDestory()
{
	CQ_DELETE(camera_, CQCamera);
	CQ_DELETE(bunnyNode_, CQSceneNode);

	CQCore::shareCore()->shareEvtDispatcher()->unregisterListener(clickListener_);
	CQCore::shareCore()->shareEvtDispatcher()->unregisterListener(wheelListener_);
}