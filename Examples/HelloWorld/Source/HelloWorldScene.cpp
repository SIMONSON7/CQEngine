#include "HelloWorldScene.h"

REGISTER_START_SCENE(HelloWorldScene)

void HelloWorldScene::onInit()
{
	dbgPuts("[HelloWorldScene] init success!");
}

void HelloWorldScene::update()
{


}

void HelloWorldScene::onDestory()
{
	dbgPuts("[HelloWorldScene] onDestory success!");
}

