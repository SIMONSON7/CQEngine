#include <stdio.h>
#include <stdarg.h>
#include <Windows.h>
#include "CQDebug.h"

NS_CQ_BEGIN

void dbgPuts(const char *_str)
{
	CQASSERT(_str);
#ifdef _MSC_VER
	OutputDebugStringA(_str);
#elif
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

NS_CQ_END

