//*****************************************************************************
//
//! \file SpotLightScene.h
//! \brief 
//! \author qiu_hao
//! \date 2019/04/01 11:45.pm
//
//*****************************************************************************
#include "CQEngine.h"

#ifndef __SPOTLIGHTSCENE_H__
#define __SPOTLIGHTSCENE_H__

USING_NS_CQ

class SpotLightScene : public CQScene
{
public:
	// NO Call onInit here.
	explicit SpotLightScene() = default;

	virtual ~SpotLightScene() = default;

public:
	virtual void onInit();

	virtual void update();

	virtual void onDestory();

public:
	void onMouseClick(void* _clickData);

	void onMouseWheel(void* _wheelData);

private:
	CQCamera* camera_;
	float camRadisZ_ = 1.0f;

	CQSceneNode * bunnyNode_;
	float modelAngle_ = 0;

	std::shared_ptr<CQEvtListener> clickListener_;
	std::shared_ptr<CQEvtListener> wheelListener_;
};

#endif /* __SPOTLIGHTSCENE_H__ */