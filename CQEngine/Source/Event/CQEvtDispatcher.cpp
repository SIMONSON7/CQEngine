#include "CQEvtDispatcher.h"
#include "CQEvtListener.h"

USING_NS_CQ;

CQEvtDispatcher::CQEvtDispatcher()
{

}

CQEvtDispatcher::~CQEvtDispatcher()
{

}

void CQEvtDispatcher::registerListener(std::shared_ptr<CQEvtListener> _listener)
{

}

void CQEvtDispatcher::unregisterListener(std::shared_ptr<CQEvtListener> _listener)
{

}

void CQEvtDispatcher::notify(CQInput::MouseEvt& _me)
{
	if (!listenerVec_.empty())
	{
		unsigned int id = static_cast<unsigned int>(_me.id_);

		for each (auto it in listenerVec_)
		{
			if (it->getEvtID() == id)
			{
				auto cb = it->getCB();
				cb->invoke();
			}
		}
	}
}

void CQEvtDispatcher::notify(CQInput::KeyboardEvt& _ke)
{

}

