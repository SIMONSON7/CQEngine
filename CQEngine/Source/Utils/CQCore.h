/*
*
*		qiu_hao		2018/08/19		09:35.pm
*/

#ifndef __CQCORE_H__
#define __CQCORE_H__

#include "CQMacros.h"

NS_CQ_BEGIN

class CQTime;
class CQScheduler;
class CQRenderer;

class CQCore
{
public:
	static
	CQCore *shareCore();

	virtual ~CQCore();

public:
	CQTime *shareCQTime();

	CQScheduler *shareCQScheduler();

	CQRenderer *shareCQRender();

	void updateTime();

	void updateScheduler();

private:
	explicit CQCore();

	// non-copyable
	CQCore(const CQCore &) = delete;

	CQCore& operator=(const CQCore &) = delete;

private:
	CQTime *time_;

	CQScheduler *scheduler_;

	CQRenderer *render_;
};

NS_CQ_END

#endif /* __CQCORE_H__ */