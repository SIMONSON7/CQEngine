#include "CQApplication.h"

USING_NS_CQ

int main(int argc,char *argv[])
{
	CQASSERT(g_app);
	g_app->Run();

	//CLEAN 
	delete g_app;
	return 0;
}


