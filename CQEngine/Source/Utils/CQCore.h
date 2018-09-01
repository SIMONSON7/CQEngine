/*
*
*		qiu_hao		2018/08/19		09:35.pm
*/

#ifndef __CQCORE_H__
#define __CQCORE_H__

#include <memory>

#include "CQMacros.h"
#include "CQDebug.h"
#include "CQMemory.h"
#include "CQMath.h"
#include "CQTime.h"
#include "CQScheduler.h"
#include "CQUtils.h"

#include "CQIO.h"
#include "CQResLoader.h"

#include "CQScene.h"
#include "CQSceneManager.h"

#include "CQRenderer.h"
#include "CQGLProgram.h"
#include "CQGLTexture.h"

NS_CQ_BEGIN

class CQCore
{
public:
	static
	CQCore *shareCore();

	virtual ~CQCore();

public:
	CQTime *ShareCQTime();

	CQScheduler *ShareCQScheduler();

private:
	explicit CQCore();

	// non-copyable
	CQCore(const CQCore &) = delete;

	CQCore& operator=(const CQCore &) = delete;

private:
	CQTime *time_;
	CQScheduler *scheduler_;
};

NS_CQ_END

#endif /* __CQCORE_H__ */