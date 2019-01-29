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

enum TexType
{
	NONE = 0,
	D1,
	D2, // Default
	D3,
	CUBE,
};

class CQTexture : public CQResI
{
public:
	CQTexture();

	virtual ~CQTexture();

public:
	inline void setResID(ResID & _resID) { resID_ = _resID; }

	inline TexType getTexType() const { return type_; }

	inline unsigned int getTexWidth() const { return width_; }

	inline unsigned int getTexHeight() const { return height_; }

	inline unsigned char * getData() const { return data_; }

public:
	virtual ResID getResID() const { return resID_; }

	virtual CQResType getResType() const { return CQResType::TEXTURE; }

	virtual void onLoadDiskRes(const std::string & _abPath);

	virtual void onDestory();

private:
	ResID resID_;

	TexType type_;

	int width_;

	int height_;

	unsigned char * data_;

};

NS_CQ_END

#endif /* __CQTEXTURE_H__ */