#include "CQSceneManager.h"

USING_NS_CQ

CQSceneManager::CQSceneManager()
{

}

CQSceneManager::~CQSceneManager()
{

}

CQSceneManager *CQSceneManager::shareSceneManager()
{
	static CQSceneManager s_sceneMgr;
	return &s_sceneMgr;
}