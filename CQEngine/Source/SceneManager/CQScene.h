//*****************************************************************************
//
//! \file CQSceneNode.h
//! \brief abstract scene node in scene graph.
//! \author qiu_hao
//! \date 2018/08/18  10:10.pm
//
//*****************************************************************************
#include <vector>
#include <memory>
#include "CQRunnable.h"
#include "CQSceneNode.h"

#ifndef __CQSCENE_H__
#define __CQSCENE_H__

NS_CQ_BEGIN

class CQScene : public CQRunnable
{
public:
	explicit CQScene();

	virtual ~CQScene();

public:
	virtual void onInit();

	virtual void update();

	virtual void onDestory();

public:
	// 0 represents the highest priority.
	void setPriority(const unsigned int  _p);

	const unsigned int getPriority() const;

protected:
	unsigned int pri_;

	CQSceneNode* rootSN_;
};

#include "CQScene.inl"

NS_CQ_END

#endif /*__CQSCENE_H__*/
