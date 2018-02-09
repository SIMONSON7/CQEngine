#include "CQApplication.h"

USING_NS_CQ

#if 1
int main(int argc,char *argv[])
{
	CQASSERT(g_app);
	g_app->Run();

	//CLEAN 
	CQ_RAW_DELETE(g_app);
	return 0;
}
#endif


