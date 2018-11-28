#include "CQEvtListener.h"
#include "CQInput.h"
#include "CQMemory.h"

USING_NS_CQ

CQEvtListener::CQEvtListener()
{

}

CQEvtListener::CQEvtListener(unsigned int _evtID, Action *_cb)
{
	evtID_ = _evtID;
	setCB(_cb);
}

CQEvtListener::~CQEvtListener()
{
	evtID_ = static_cast<unsigned int>(CQInput::EvtID::NONE);
	if (cb_)
	{
		CQ_RAW_DELETE(cb_);
	}
}

void CQEvtListener::setEvtID(unsigned int _evtID)
{
	evtID_ = _evtID;
}

void CQEvtListener::setCB(Action *_cb)
{
	if (_cb)
	{
		CQ_RAW_DELETE(cb_);
		cb_ = _cb;
	}
}

Action* CQEvtListener::getCB()
{
	if (cb_)
	{
		return cb_;
	}
	else
	{
		return nullptr;
	}
}

unsigned int CQEvtListener::getEvtID() const
{
	return evtID_;
}

bool CQEvtListener::isCBValid()
{
	if (getCB())
	{
		return true;
	}
	return false;
}

