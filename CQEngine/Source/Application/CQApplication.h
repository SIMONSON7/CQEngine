/*
*
*		qiu_hao		2018/02/05		18:21.pm
*/
#ifndef __CQAPPLICATION_H__
#define __CQAPPLICATION_H__

#include "CQMacros.h"

NS_CQ_BEGIN

class CQAppI
{
public:
	virtual void Run() = 0;


};

NS_CQ_END

extern NS_CQ::CQAppI *g_app;

#endif /*__CQAPPLICATION_H__*/



