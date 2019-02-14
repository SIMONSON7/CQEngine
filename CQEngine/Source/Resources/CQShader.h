//*****************************************************************************
//
//! \file CQShader.h
//! \brief 
//! \author qiu_hao
//! \date 2019/02/01 03:53.pm
//
//*****************************************************************************
#ifndef __CQSHADER_H__
#define __CQSHADER_H__

#include "CQMacros.h"
#include "CQResI.h"
#include "ResID.h"
#include "CQNoncopyable.h"

NS_CQ_BEGIN

struct RawData;

enum class ShaderType
{
	NONE = 0X0,
	VERTEX,
	PIXEL,
	GEOMETRY
};

class CQShader : public CQResI, private CQNoncopyable
{
public:
	CQShader() = default;

	CQShader(ShaderType _type);

	virtual ~CQShader();

public:
	inline void setShader(ShaderType _type) { type_ = _type; }

	inline ShaderType getShaderType() const { return type_; }

public:
	virtual ResID getResID() const { return resID_; }

	virtual ResType getResType() const { return ResType::SHADER; }

	virtual void onLoadDiskRes(const std::string & _abPath);

	virtual void onDestory();

private:
	ResID resID_;

	ShaderType type_;

	RawData * data_;

};

NS_CQ_END

#endif /* __CQSHADER_H__ */