//*****************************************************************************
//
//! \file TexExScene.h
//! \brief 
//! \author qiu_hao
//! \date 2019/06/19 11:49.pm
//
//*****************************************************************************
#include "CQEngine.h"

#ifndef __TEXEXSCENE_H__
#define __TEXEXSCENE_H__

USING_NS_CQ

class TexExScene : public CQScene
{
public:
	// NO Call onInit here.
	explicit TexExScene() = default;

	virtual ~TexExScene() = default;

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
	float modelAngle_ = 0;

	CQPrefab * cube_;
	CQPrefab * plane_;

	std::shared_ptr<CQEvtListener> clickListener_;
	std::shared_ptr<CQEvtListener> wheelListener_;
};

#endif /* __TEXEXSCENE_H__ */

