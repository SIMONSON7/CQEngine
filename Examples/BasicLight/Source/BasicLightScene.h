//*****************************************************************************
//
//! \file BasicLightScene.h
//! \brief 
//! \author qiu_hao
//! \date 2019/02/27 02:27.pm
//
//*****************************************************************************
#include "CQEngine.h"

#ifndef __BASICLIGHTSCENE_H__
#define __BASICLIGHTSCENE_H__

USING_NS_CQ

class BasicLightScene : public CQScene
{
public:
	// NO Call onInit here.
	explicit BasicLightScene() = default;

	virtual ~BasicLightScene() = default;

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

	bool isADS_;

	std::shared_ptr<CQEvtListener> clickListener_;
	std::shared_ptr<CQEvtListener> wheelListener_;
};

#endif /* __BASICLIGHTSCENE_H__ */