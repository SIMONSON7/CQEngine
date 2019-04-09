//*****************************************************************************
//
//! \file BasicTexScene.h
//! \brief 
//! \author qiu_hao
//! \date 2019/04/09 11:33.pm
//
//*****************************************************************************
#include "CQEngine.h"

#ifndef __BASICTEXSCENE_H__
#define __BASICTEXSCENE_H__

USING_NS_CQ

class BasicTexScene : public CQScene
{
public:
	// NO Call onInit here.
	explicit BasicTexScene() = default;

	virtual ~BasicTexScene() = default;

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

	//CQSceneNode * bunnyNode_;
	//float modelAngle_ = 0;

	std::shared_ptr<CQEvtListener> clickListener_;
	std::shared_ptr<CQEvtListener> wheelListener_;
};

#endif /* __BASICTEXSCENE_H__ */