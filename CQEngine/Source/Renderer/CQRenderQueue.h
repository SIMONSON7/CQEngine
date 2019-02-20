//*****************************************************************************
//
//! \file CQRenderQueue.h
//! \brief 
//! \author qiu_hao
//! \date 2019/02/12 02:55.pm
//
//*****************************************************************************
#ifndef __CQRENDERQUEUE_H__
#define __CQRENDERQUEUE_H__

#include <vector>
#include "CQMacros.h"
#include "CQNoncopyable.h"

NS_CQ_BEGIN

class CQMeshRenderer;

class CQRenderQueue : private CQNoncopyable
{
public:
	~CQRenderQueue();

public:
	void pushNormalQueue(CQMeshRenderer* _com);

	void pushTransQueue(CQMeshRenderer* _com);

	void clearAll();

private:
	explicit CQRenderQueue();

	friend class CQRenderer;

private:
	std::vector<CQMeshRenderer*> normalQueue_;

	std::vector<CQMeshRenderer*> transQueue_;

};

NS_CQ_END

#endif /* __CQRENDERQUEUE_H__ */