//*****************************************************************************
//
//! \file CQAny.h
//! \brief An implementation of std::any (C++17).
//! \author qiu_hao
//! \date 2019/03/04 05:51.pm
//
//*****************************************************************************
#ifndef __CQANY_H__
#define __CQANY_H__

#include <iostream>
#include <typeindex>
#include <memory>
#include "CQMacros.h"
#include "CQMemory.h"

NS_CQ_BEGIN;

class CQAny
{
public:
	CQAny()
		:
		tIdx_(typeid(void))
	{}

	CQAny(const CQAny & _other)
		:
		tIdx_(_other.tIdx_),
		ptr_(_other.ptr_->move())
	{}

	CQAny(CQAny && _other)
		:
		tIdx_(_other.tIdx_),
		ptr_(std::move(_other.ptr_))
	{}

	template<typename T, 
			 class = typename std::enable_if<!std::is_same<std::decay<T>::type, CQAny>::value, T>
											::type>
	CQAny(T && _other)
		:
		tIdx_(typeid(std::decay<T>::type)),
		ptr_(new Derived<std::decay<T>::type>(std::forward<T>(_other)))
	{}

	CQAny & operator=(const CQAny & _other)
	{
		if (ptr_ == _other.ptr_)
		{
			return *this;
		}

		tIdx_ = _other.tIdx_;
		ptr_ = _other.ptr_->move();
		return *this;
	}

public:
	bool isNull()
	{
		return !bool(ptr_);
	}

	// CQAny any;
	// any = 1;
	// any.is<int>();
	template<typename T>
	bool is() const
	{
		return tIdx_ == type_index(typeid(T));
	}

	// any.cast<string>();
	template<typename T>
	T & cast()
	{
		if (!is<T>())
		{
			throw bad_cast();
		}

		// core
		auto d = std::dynamic_cast<Derived<T>*>(ptr_->get());
		return d->value_;
	}

private:
	struct Base;
	using BaseUPtr = std::unique_ptr<Base>;

	// Just placeholder
	struct Base
	{
		virtual ~Base() {}
		virtual BaseUPtr move() const = 0;
	};

	// Hold type info : T
	template<typename T>
	struct Derived : Base
	{
		template<typename U>
		Derived( U && _v )
			:
			value_(std::forward<U>(_v))
		{}


		BaseUPtr move() const
		{
			return BaseUPtr(new Derived<T>(value_));
		}

		T value_;
	};

private:


private:
	BaseUPtr ptr_;

	// type_index is a wrapper class around a std::type_info obj;
	std::type_index tIdx_;
};

NS_CQ_END;

#endif /* __CQANY_H__ */
