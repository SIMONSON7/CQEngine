#include "CQEvtDispatcher.h"

USING_NS_CQ;

CQEvtDispatcher *CQEvtDispatcher::shareDispatcher()
{
	static CQEvtDispatcher s_dispatcher;
	return &s_dispatcher;
}

CQEvtDispatcher::CQEvtDispatcher()
{

}

CQEvtDispatcher::~CQEvtDispatcher()
{

}
