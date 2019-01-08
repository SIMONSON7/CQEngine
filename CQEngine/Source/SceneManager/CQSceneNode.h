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
#include <string>
#include "CQMacros.h"
#include "CQNoncopyable.h"
#include "CQObject.h"

NS_CQ_BEGIN

class CQSceneNode : public CQNoncopyable 
{
public:
	typedef std::vector<CQSceneNode*> SceneNodePtrVec;

	typedef std::string string;

public:
	CQSceneNode(CQSceneNode* _parent, const string& _name);

	virtual ~CQSceneNode();

public:
	void attachParent(CQSceneNode* _parent);

	void attachChild(CQSceneNode* _child);

	void attachObj(CQObject* _obj);

	void detach(const string& _childName);

	void detachChildren();

protected:
	CQSceneNode* parent_;

	SceneNodePtrVec children_;

private:
	CQObject* obj_;

	string name_;
};

NS_CQ_END

#endif /* __CQSCENENODE_H__ */