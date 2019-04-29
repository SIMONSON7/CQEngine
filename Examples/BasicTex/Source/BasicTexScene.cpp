#include "BasicTexScene.h"

USING_NS_CQ;

REGISTER_START_SCENE(BasicTexScene)

void BasicTexScene::onInit()
{
	dbgPuts("[BasicTexScene] init success!");

	// camera
	// TODO : should have a default camera.
	camera_ = CQ_NEW(CQCamera);

	// Evt
	CQEvtDispatcher* dispatcher = CQCore::shareCore()->shareEvtDispatcher();

	clickListener_ = std::make_shared<CQEvtListener>();
	clickListener_->setEvtID(CQInput::EvtID::MOUSE_L_CLICK_BEGIN);
	clickListener_->setCB(std::bind(&BasicTexScene::onMouseClick, this, std::placeholders::_1));

	wheelListener_ = std::make_shared<CQEvtListener>();
	wheelListener_->setEvtID(CQInput::EvtID::MOUSE_WHEEL);
	wheelListener_->setCB(std::bind(&BasicTexScene::onMouseWheel, this, std::placeholders::_1));

	dispatcher->registerListener(clickListener_);
	dispatcher->registerListener(wheelListener_);

	// shader 
	auto program = CQ_NEW(CQShaderProgram);
	auto vs = std::dynamic_pointer_cast<CQShader>(CQCore::shareCore()->shareResManager()->getRes(VNAME(ResIDDef::DEF_PHONG_VERTEX_SHADER)));
	auto fs = std::dynamic_pointer_cast<CQShader>(CQCore::shareCore()->shareResManager()->getRes(VNAME(ResIDDef::DEF_PHONG_FRAGMENT_SHADER)));
	program->attachNativeShader((const char *)(vs->getRawData()->data_), ShaderType::VERTEX);
	program->attachNativeShader((const char *)(fs->getRawData()->data_), ShaderType::PIXEL);
	program->genProgram();

	// texture
	auto texture = CQ_NEW(CQTexture);
	//auto img = std::dynamic_pointer_cast<CQImg>(CQCore::shareCore()->shareResManager()->getRes(VNAME(ResIDDef::HELLOWORLD_WALL_TEX)));
	//texture->setRawImg(img.get());

	// material
	auto material = CQ_NEW(CQMaterial);
	material->setProgram(program);
	material->setTex(MTexType::AMBIENT, texture);

	// Prefab
	cube_ = CQPrefabFactory::createCube(1.0f);
	if (cube_)
	{
		cube_->setupSurface(material);

		// transform
		cube_->getSceneNode()->getObj()->
			getTransform()->moveTo(Vector3(0, -1.5f, -1.5f));

		cube_->getSceneNode()->getObj()->
			getTransform()->rotateY(35.0f);
	}

	plane_ = CQPrefabFactory::createPlane(50.0f, 50.0f, 1, 1);
	if (plane_)
	{
		plane_->setupSurface(nullptr);
	}
}

void BasicTexScene::update()
{
	// program
	auto mr = std::dynamic_pointer_cast<CQMeshRenderer>(cube_->getSceneNode()->getObj()->getComponentByName("MeshRender"));
	auto program = (*mr->getMaterials())[0]->getProgram();
	program->load();

	// bunny transform
	auto bunnyTrans = cube_->getSceneNode()->getObj()->getTransform();
	//bunnyTrans->rot(++modelAngle_, bunnyTrans->getUp()); // rot self axis.
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
	program->setVector("uLight.pos", viewMat * Vector4(10.0f, 10.0f, 10.0f, 1.0f));
	program->setVector("uLight.a", Vector3(0.4f, 0.4f, 0.4f));
	program->setVector("uLight.d", Vector3(1.0f, 1.0f, 1.0f));
	program->setVector("uLight.s", Vector3(1.0f, 1.0f, 1.0f));

	program->setVector("uMat.a", Vector3(0.9f, 0.5f, 0.3f));
	program->setVector("uMat.d", Vector3(0.9f, 0.5f, 0.3f));
	program->setVector("uMat.s", Vector3(0.8f, 0.8f, 0.8f));
	program->setFloat("uMat.shineFactor", 110.0f);

	program->setMatrix("uModelViewMatrix", mv);
	program->setMatrix("uMVP", mvp);
	program->setMatrix("uNormalMatrix", Matrix3(Vector3(mv[0].x, mv[0].y, mv[0].z),
		Vector3(mv[1].x, mv[1].y, mv[1].z),
		Vector3(mv[2].x, mv[2].y, mv[2].z)));
}

void BasicTexScene::onDestory()
{
	CQ_DELETE(camera_, CQCamera);

	CQPrefabFactory::destroyCube(cube_);
	CQPrefabFactory::destroyPlane(plane_);

	CQCore::shareCore()->shareEvtDispatcher()->unregisterListener(clickListener_);
	CQCore::shareCore()->shareEvtDispatcher()->unregisterListener(wheelListener_);
}

void BasicTexScene::onMouseClick(void* _clickData)
{
	if (_clickData)
	{
		CQInput::MouseEvt *evt = static_cast<CQInput::MouseEvt*>(_clickData);
		if (evt && evt->id_ == CQEngine::CQInput::MOUSE_L_CLICK_BEGIN)
		{
			dbgPrintf("[BasicLightScene] click x : %d", evt->x_);
		}
	}
}

void BasicTexScene::onMouseWheel(void* _wheelData)
{
	if (_wheelData)
	{
		CQInput::MouseEvt *evt = static_cast<CQInput::MouseEvt*>(_wheelData);
		if (evt && evt->id_ == CQEngine::CQInput::MOUSE_WHEEL)
		{
			dbgPrintf("[BasicLightScene] wheel delta : %d", evt->delta_);

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
