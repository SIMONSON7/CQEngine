//*****************************************************************************
//
//! \file CQSceneNode.h
//! \brief abstract scene node in scene graph.
//! \author qiu_hao
//! \date 2019/01/07 10:44.pm
//
//*****************************************************************************
#ifndef __CQSCENENODE_H__
#define __CQSCENENODE_H__

#include <vector>
#include <memory>
#include "CQMacros.h"
#include "CQNoncopyable.h"
#include "CQObject.h"

NS_CQ_BEGIN

class CQSceneNode : public CQNoncopyable 
{
public:


private:
	std::unique_ptr<CQSceneNode> parent_;

	std::vector<std::unique_ptr<CQSceneNode>> children_;

private:
	std::unique_ptr<CQObject> obj_;
};

NS_CQ_END

#endif /* __CQSCENENODE_H__ */