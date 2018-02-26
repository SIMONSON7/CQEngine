/*
*
*		qiu_hao		2018/02/23		09:29.pm
*/
#ifndef __CQTUPLE_H__
#define __CQTUPLE_H__

#include "CQMacros.h"

NS_CQ_BEGIN

template <size_t DIMENSION, typename TYPE>
class Tuple
{
public:
	Tuple();
	Tuple(const Tuple& _tuple);
	~Tuple();

public:
	///
	inline operator const TYPE* () const;
	inline operator TYPE* ();
	inline const TYPE& operator[] (int _i) const;
	inline TYPE& operator[] (int _i);

	///
	Tuple& operator= (const Tuple& _tuple);

	///
	bool operator== (const Tuple& _tuple) const;
	bool operator!= (const Tuple& _tuple) const;
	bool operator<  (const Tuple& _tuple) const;
	bool operator<= (const Tuple& _tuple) const;
	bool operator>  (const Tuple& _tuple) const;
	bool operator>= (const Tuple& _tuple) const;

protected:
	TYPE mTuple[DIMENSION];

};

#include "CQTuple.inl"

NS_CQ_END

#endif /* __CQTUPLE_H__ */
