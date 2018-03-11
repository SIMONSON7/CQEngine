/*
*
*		qiu_hao		2018/03/10		11:02.pm
*/
#ifndef __CQOBJECT_H__
#define __CQOBJECT_H__

#include "CQMacros.h"
#include <string>

NS_CQ_BEGIN

class CQObject
{
public:
	explicit CQObject() {}
	virtual ~CQObject();
public:
	void setName(const std::string _name);
	const std::string& getName() const;

	const uint32_t getTag() const;
	void setTag(uint32_t _tag);

public:
	
protected:
	std::string name_;
	//CQObject *parent_;
	uint32_t tag_;
};

#include "CQObject.inl"

NS_CQ_END

#endif /*__CQOBJECT_H__*/