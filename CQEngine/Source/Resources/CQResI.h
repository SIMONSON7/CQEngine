//*****************************************************************************
//
//! \file CQResI.h
//! \brief Interface that represents content that can be read form disk.
//! \author qiu_hao
//! \date 2019/01/25 05:09.pm
//
//*****************************************************************************
#ifndef __CQRESI_H__
#define __CQRESI_H__

#include <string>
#include "CQMacros.h"
#include "ResID.h"

NS_CQ_BEGIN

enum ResType
{
	NONE = 0,
	TEXTURE,
	SHADER,
	MESH
};

class CQResI
{
public:
	virtual ResID getResID() const = 0;
	virtual ResType getResType() const = 0;
	virtual void onLoadDiskRes(const std::string & _abPath) = 0;
	virtual void onDestory() = 0;
};

NS_CQ_END

#endif /* __CQRESI_H__ */
