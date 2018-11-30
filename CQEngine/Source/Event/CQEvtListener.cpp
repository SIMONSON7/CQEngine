#include "CQEvtListener.h"
#include "CQInput.h"

USING_NS_CQ

CQEvtListener::CQEvtListener()
{

}

CQEvtListener::CQEvtListener(unsigned int _evtID, CQEvtListener::Callback& _cb)
	:
	evtID_(_evtID),
	cb_(_cb)
{

}

CQEvtListener::~CQEvtListener()
{
	evtID_ = static_cast<unsigned int>(CQInput::EvtID::NONE);
	cb_ = nullptr;
}

void CQEvtListener::setEvtID(unsigned int _evtID)
{
	evtID_ = _evtID;
}

void CQEvtListener::setCB(CQEvtListener::Callback _cb)
{
	cb_ = nullptr;
	cb_ = _cb;
}

CQEvtListener::Callback CQEvtListener::getCB()
{
	return cb_;
}

unsigned int CQEvtListener::getEvtID() const
{
	return evtID_;
}

bool CQEvtListener::isCBValid()
{
	if (cb_ == nullptr)
	{
		return false;
	}
	return true;
}

