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
#include "CQNoncopyable.h"

NS_CQ_BEGIN

enum TexType
{
	D1,
	D2, // Default
	D3,
	CUBE,
};

struct Img
{
	enum Format
	{
		NONE,
		RED,
		RGB,
		RGBA
	};

	int width_;
	int height_;
	Format format_;
	unsigned char * data_;
};

class CQTexture : public CQResI, private CQNoncopyable
{
public:
	CQTexture();

	virtual ~CQTexture();

public:
	inline void setResID(ResID & _resID) { resID_ = _resID; }

	inline TexType getTexType() const { return type_; }

	inline unsigned int getTexWidth() const { return img_->width_; }

	inline unsigned int getTexHeight() const { return img_->height_; }

	inline unsigned char * getData() const { return img_->data_; }

public:
	virtual ResID getResID() const { return resID_; }

	virtual ResType getResType() const { return ResType::TEXTURE; }

	virtual void onLoadDiskRes(const std::string & _abPath);

	virtual void onDestory();

private:
	ResID resID_;

	TexType type_;

	Img * img_;

};

NS_CQ_END

#endif /* __CQTEXTURE_H__ */