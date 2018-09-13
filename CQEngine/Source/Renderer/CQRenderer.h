/*
*
*		qiu_hao		2018/03/31		05:57.pm
*/
#ifndef __CQRENDERER_H__
#define __CQRENDERER_H__

#include "CQMacros.h"
#if defined(_MSC_VER)
	#include "CQWglContext.h"
#endif

NS_CQ_BEGIN

class CQRenderer
{
public:
	virtual ~CQRenderer();

public:
	void init();

	void update();

	void destory();

private:
	friend class CQCore;

	explicit CQRenderer();

	// non-copyable
	CQRenderer(const CQRenderer &) = delete;

	CQRenderer& operator=(const CQRenderer &) = delete;

private:
#if defined(_MSC_VER)
	CQWglContext ctx_;
#endif
};

NS_CQ_END

#endif /*__CQRENDERER_H__*/

