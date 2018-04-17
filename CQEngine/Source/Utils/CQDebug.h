/*
*
*		qiu_hao		2017/12/28		02:18.pm
*/
#ifndef __CQDEBUG_H__
#define __CQDEBUG_H__

#include "CQMacros.h"
#include "CQWglContext.h"

NS_CQ_BEGIN

#if defined(CQDEBUG)
#	define CQ_DBGPUTS()
#	define CQ_DBGPRINTF()
#	define CQ_GETSOCKETERROR()
#	define CQ_GLCHECK(_call) 
#else
#	define CQ_DBGPUTS()
#	define CQ_DBGPRINTF()
#	define CQ_GETSOCKETERROR()
#	define CQ_GLCHECK(_call) _call;
#endif

void dbgPuts(const char *_str);

void dbgPrintf(const char *_format,...);

int getSocketError(int *_errno = 0);

GLenum glCheckError(const char *_file, int _line)
{
	GLenum err;

	return err;
}
#define GLCHECKERROR glCheckError(__FILE__, __LINE__)

NS_CQ_END

#endif /*__CQDEBUG_H__*/