//*****************************************************************************
//
//! \file CQInput.h
//! \brief User input interface.
//! \author qiu_hao
//! \date 2018/11/28 02:28.pm
//
//*****************************************************************************
#ifndef __CQINPUT_H__
#define __CQINPUT_H__

#include "CQMacros.h"

NS_CQ_BEGIN

class CQInput
{
public:
	// Built-in event IDs.
	enum EvtID
	{
		NONE = 0,
		// Mouse
		MOUSE_L_CLICK_BEGIN,
		MOUSE_R_CLICK_BEGIN,
		MOUSE_L_CLICK_END,
		MOUSE_R_CLICK_END,
		MOUSE_L_DOUBLE_CLICK,
		MOUSE_WHEEL,
		// Touch
		TOUCH,
		// Keyboard
		KEYBOARD,
	};

	struct Evt
	{
		EvtID id_;
	};

	struct MouseEvt : public Evt
	{
		int x_;
		int y_;
		int delta_;
	};

	struct KeyboardEvt : public Evt
	{

	};

	struct tmp
	{

	};
};



NS_CQ_END

#endif /* __CQINPUT_H__ */