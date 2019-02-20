#include "SkyBoxScene.h"

REGISTER_START_SCENE(SkyBoxScene)

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
	auto vs = std::dynamic_pointer_cast<CQShader>(CQCore::shareCore()->shareResManager()->getRes(VNAME(ResIDDef::DEF_VERTEX_SHADER)));
	auto fs = std::dynamic_pointer_cast<CQShader>(CQCore::shareCore()->shareResManager()->getRes(VNAME(ResIDDef::DEF_NO_TEX_FRAGMENT_SHADER)));
	program->attachNativeShader((const char *)(vs->getRawData()->data_), ShaderType::VERTEX);
	program->attachNativeShader((const char *)(fs->getRawData()->data_), ShaderType::PIXEL);
	program->genProgram();

	// TODO
	program_ = program;

	// material
	auto material = CQ_NEW(CQMaterial);
	material->setProgram(program);
	std::vector<CQMaterial*> materials;
	materials.push_back(material);

	// meshRender
	auto bunnyMR = std::make_shared<CQMeshRenderer>();
	bunnyMR->setup(bunnyMesh.get(), nullptr, materials);

	bunnyObj->setComponent(std::dynamic_pointer_cast<CQComponent>(bunnyMR));

	//// move
	//bunnyObj->getTransform()->moveTo(Vector3(0, 10, 0));
}

void SkyBoxScene::update()
{
	auto transform = camera_->getTransform();
	transform->buildLocalCoordinate(Vector3(0, 0, camRadisZ_), Vector3(0, 0, 0), Vector3(0, 1, 0));
	float aspect(800.0f / 600.0f);
	auto viewMat = transform->calWorldToLcalMatRH();
	auto projMat = camera_->calPerspectiveMat(60, aspect, 0.1f, 100.0f);

	// program
	program_->load();

	//tmat4x4<T>& rotate(value_type angle, tvec3<T> const & v)
	Matrix4 tmp(1.0f);
	Vector3 v(0.0f, 1.0f, 0.0f);
	Matrix4 rotateMat = rotate(tmp, ++modelAngle_, v);
	Matrix4 modelMat = rotateMat;

	Matrix4 mvp = projMat * viewMat * modelMat;
	program_->setMatrix("mvp", mvp);



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
	CQ_DELETE(bunnyNode_, CQSceneNode);

	CQCore::shareCore()->shareEvtDispatcher()->unregisterListener(clickListener_);
	CQCore::shareCore()->shareEvtDispatcher()->unregisterListener(wheelListener_);
}