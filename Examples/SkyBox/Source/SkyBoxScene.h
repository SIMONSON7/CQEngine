//*****************************************************************************
//
//! \file SkyBoxScene.h
//! \brief 
//! \author qiu_hao
//! \date 2019/02/15 11:58.am
//
//*****************************************************************************
#include "CQEngine.h"

#ifndef __SKYBOXSCENE_H__
#define __SKYBOXSCENE_H__

USING_NS_CQ

class SkyBoxScene : public CQScene
{
public:
	// NO Call onInit here.
	explicit SkyBoxScene() = default;

	virtual ~SkyBoxScene() = default;

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
	CQShaderProgram * program_;
	float modelAngle_ = 0;

	std::shared_ptr<CQEvtListener> clickListener_;
	std::shared_ptr<CQEvtListener> wheelListener_;
};

#endif /* __SKYBOXSCENE_H__ */