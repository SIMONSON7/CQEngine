#include "CQApplicationBase.h"

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

USING_NS_CQ

int main(int argc, char *argv[])
{
	CQASSERT(g_pApplication);

	g_pApplication->initialize();

	while (!g_pApplication->isQuit())
	{
		g_pApplication->tick();
	}

	g_pApplication->finalize();

	//------------------------------------------------------------
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	return EXIT_SUCCESS;
}
