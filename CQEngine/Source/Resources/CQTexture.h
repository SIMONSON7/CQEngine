//*****************************************************************************
//
//! \file CQTexture.h
//! \brief 
//! \author qiu_hao
//! \date 2019/01/29 02:29.pm
//
//*****************************************************************************
#ifndef __CQTEXTURE_H__
#define __CQTEXTURE_H__

#include "CQMacros.h"
#include "CQResI.h"
#include "ResID.h"

NS_CQ_BEGIN

class CQTexture : public CQResI
{
public:
	CQTexture();

	virtual ~CQTexture();

public:
	virtual ResID getResID() const { return resID_; }

	virtual CQResType getResType() const { return CQResType::TEXTURE; }

	virtual void onLoadDiskRes(const std::string & _abPath);

	virtual void onDestory();

private:
	ResID resID_;

};

NS_CQ_END

#endif /* __CQTEXTURE_H__ */