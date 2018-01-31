/*
*
*		qiu_hao		2017/12/28		02:18.pm
*/
#ifndef __CQDEBUG_H__
#define __CQDEBUG_H__

#include "CQMacros.h"

NS_CQ_BEGIN

void dbgPuts(const char *_str);

void dbgPrintf(const char *_format,...);

int getSocketError(int *_errno = 0);



NS_CQ_END

#endif /*__CQDEBUG_H__*/