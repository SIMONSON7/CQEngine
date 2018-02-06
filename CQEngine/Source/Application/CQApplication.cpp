#include "CQApplication.h"
#include "CQMacros.h"

USING_NS_CQ

int main(int argc,char *argv[])
{
	CQASSERT(g_app);
	g_app->Run();
	delete g_app;
	return 0;
}
