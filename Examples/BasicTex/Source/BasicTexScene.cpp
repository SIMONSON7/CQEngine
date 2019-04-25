#include "BasicTexScene.h"

USING_NS_CQ;

REGISTER_START_SCENE(BasicTexScene)

void BasicTexScene::onInit()
{
	cube_ = CQPrefabFactory::createCube(1.0f);
	if (cube_)
	{
		cube_->setupSurface(nullptr);
	}

	//auto planePrefab = CQPrefabFactory::createPlane(50.0f, 50.0f, 1, 1);
	//if (planePrefab)
	//{
	//	planePrefab->setupSurface(nullptr);
	//	plane_ = planePrefab->getSceneNode();
	//}
}

void BasicTexScene::update()
{

}

void BasicTexScene::onDestory()
{
	CQPrefabFactory::destroyCube(cube_);
}

void BasicTexScene::onMouseClick(void* _clickData)
{

}

void BasicTexScene::onMouseWheel(void* _wheelData)
{

}
