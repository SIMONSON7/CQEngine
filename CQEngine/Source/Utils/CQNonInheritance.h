//*****************************************************************************
//
//! \file CQNonInheritance.h
//! \brief The non inheritable base class.
//! \author qiu_hao
//! \date 2018/10/06 22:47.pm
//
//*****************************************************************************
#ifndef __CQNONINHERITANCE_H__
#define __CQNONINHERITANCE_H__

#include "CQMacros.h"

template<typename T>
class CQNonInheritance
{
public:
	friend T;
private:
	CQNonInheritance() {}
	~CQNonInheritance() {}
};

#endif /* __CQNONINHERITANCE_H__ */
