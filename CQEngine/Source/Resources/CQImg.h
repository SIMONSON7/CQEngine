//*****************************************************************************
//
//! \file CQImg.h
//! \brief 
//! \author qiu_hao
//! \date 2019/04/29 10:50.pm
//
//*****************************************************************************
#ifndef __CQIMG_H__
#define __CQIMG_H__

#include "CQMacros.h"
#include "CQResI.h"
#include "ResID.h"
#include "CQNoncopyable.h"

NS_CQ_BEGIN

class CQImg : public CQResI, private CQNoncopyable
{
public:
	enum Format
	{
		NONE = 0X0,
		RED,
		RGB,
		RGBA
	};

public:
	CQImg();

	virtual ~CQImg();

public:
	inline void setResID(ResID & _resID) { resID_ = _resID; }

	inline unsigned int getWidth() const { return width_; }

	inline unsigned int getHeight() const { return height_; }

	inline unsigned char * getData() const { return data_; }

public:
	virtual ResID getResID() const { return resID_; }

	virtual ResType getResType() const { return ResType::IMG; }

	virtual void onLoadDiskRes(const std::string & _abPath);

	virtual void onDestory();

private:
	ResID resID_;

	int width_;

	int height_;

	Format format_;

	unsigned char * data_;
};

NS_CQ_END

#endif /* __CQIMG_H__ */





