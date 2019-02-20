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
	static CQSceneNode * s_root_;
public:
	typedef std::vector<CQSceneNode*> SceneNodePtrVec;

	typedef std::string string;

public:
	CQSceneNode(CQSceneNode * _parent, CQObject * _obj, const string & _name);

	virtual ~CQSceneNode();

public:
	bool attachChild(CQSceneNode* _child);

	void attachObj(CQObject* _obj);

	bool detach(const string & _childName);

	void detachChildren();

	inline CQSceneNode* getParent() { return parent_; }

	inline SceneNodePtrVec & getChildren() { return children_; }

	inline CQObject* getObj() { return obj_; }

	inline const string & getName() const { return name_; }

	inline void setIsDirty(bool _v) { isDirty_ = _v; }

	inline bool isDirty() const { return isDirty_; }

private:
	void __updateGraph(CQSceneNode* _root);

private:
	friend class CQCuller;

protected:
	CQSceneNode* parent_;

	SceneNodePtrVec children_;

private:
	CQObject* obj_;

	string name_;

	bool isDirty_;

	bool isVisited_;
};

NS_CQ_END

#endif /* __CQSCENENODE_H__ */