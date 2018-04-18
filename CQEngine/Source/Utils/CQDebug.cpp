#include <stdio.h>
#include <stdarg.h>

#if defined(_MSC_VER)
	#include <Windows.h>
#else
	#include <errno.h>
#endif
#include "CQDebug.h"

NS_CQ_BEGIN

void dbgPuts(const char *_str)
{
	CQASSERT(_str);
#ifdef _MSC_VER
	OutputDebugStringA(_str);
#else
	puts(_str);
#endif
}

void dbgPrintf(const char *_format, ...)
{
	char buff[MAX_STRBUFF_SIZE];
	char *str = buff;
	va_list list;
	va_start(list, _format);
	size_t len = vsnprintf(buff, sizeof(buff), _format, list);
	CQASSERT(len < sizeof(buff));
	str[len] = '\0';
	dbgPuts(str);
	va_end(list);
}

int getSocketError(int *_errno )
{
#ifdef _MSC_VER
	return WSAGetLastError();
#else
	return (*_errno);
#endif
}

GLenum getGLError(const char *_file, int _line)
{
	GLenum err;
	if ((err = glGetError()) != GL_NO_ERROR)
	{
		dbgPrintf("[GLERROR]\n\tCODE : %d \n\tFILE : %s \n\tLINE : %d \n[GLERROR]\n", (GLint)err, _file, _line);
	}
	return err;
}

NS_CQ_END

