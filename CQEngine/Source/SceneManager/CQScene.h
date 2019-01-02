/*
*
*		qiu_hao		2018/08/18		10:10.pm
*/
#include <vector>
#include <memory>
#include "CQObject.h"

#ifndef __CQSCENE_H__
#define __CQSCENE_H__

NS_CQ_BEGIN

class CQScene : public CQObject
{
public:
	explicit CQScene();

	virtual ~CQScene();
public:
	///
	virtual void onInit();

	///
	virtual void update();

	///
	virtual void onDestory();

public:
	// 0 represents the highest priority.
	void setPriority(const unsigned int  _p);

	const unsigned int getPriority() const;

protected:
	unsigned int p_;

	std::vector<std::shared_ptr<CQObject>> nodes_;
};

#include "CQScene.inl"

NS_CQ_END

#endif /*__CQSCENE_H__*/
