//*****************************************************************************
//
//! \file LightExScene.h
//! \brief 
//! \author qiu_hao
//! \date 2019/02/28 06:37.pm
//
//*****************************************************************************
#include "CQEngine.h"

#ifndef __LIGHTEXSCENE_H__
#define __LIGHTEXSCENE_H__

USING_NS_CQ

class LightExScene : public CQScene
{
public:
	// NO Call onInit here.
	explicit LightExScene() = default;

	virtual ~LightExScene() = default;

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

	// TMP
	CQPointLight lights_[5];

	std::shared_ptr<CQEvtListener> clickListener_;
	std::shared_ptr<CQEvtListener> wheelListener_;
};

#endif /* __LIGHTEXSCENE_H__ */