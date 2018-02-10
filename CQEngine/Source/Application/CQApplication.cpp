#include "CQApplication.h"

#ifdef _DEBUG
//#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
//#define new DEBUG_CLIENTBLOCK
#endif

#define _CRTDBG_MAP_ALLOC 

USING_NS_CQ

#if 1
int main(int argc,char *argv[])
{
	CQASSERT(g_app);
	g_app->run();

	//CLEAN 
	CQ_DELETE(g_app, CQAppI);

	//------------------------------------------------------------
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return 0;
}
#endif


