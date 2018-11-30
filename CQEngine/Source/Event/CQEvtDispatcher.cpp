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
	listenerVec_.push_back(_listener);
}

void CQEvtDispatcher::unregisterListener(std::shared_ptr<CQEvtListener> _listener)
{

}

void CQEvtDispatcher::notify(CQInput::Evt* _evt)
{
	if (!listenerVec_.empty() && _evt != nullptr)
	{
		unsigned int id = static_cast<unsigned int>(_evt->id_);

		for each (auto it in listenerVec_)
		{
			if (it->getEvtID() == id)
			{
				if (it->isCBValid())
				{
					it->getCB()(static_cast<void*>(_evt));
				}
			}
		}
	}
}

