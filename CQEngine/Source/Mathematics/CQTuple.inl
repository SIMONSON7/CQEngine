template <size_t DIMENSION, typename TYPE>
Tuple<DIMENSION,TYPE>::Tuple()
{

}

template <size_t DIMENSION, typename TYPE>
Tuple<DIMENSION, TYPE>::Tuple(const Tuple& _tuple)
{
	for (int i = 0; i < DIMENSION; ++i)
	{
		mTuple[i] = _tuple.mTuple[i];
	}
}

template <size_t DIMENSION, typename TYPE>
Tuple<DIMENSION, TYPE>::~Tuple()
{

}

// *ptr
template <size_t DIMENSION, typename TYPE>
inline Tuple<DIMENSION, TYPE>::operator const TYPE* () const
{
	return mTuple;
}

// *ptr
template <size_t DIMENSION, typename TYPE>
inline Tuple<DIMENSION, TYPE>::operator TYPE* ()
{
	return mTuple;
}

// tuple[i]
template <size_t DIMENSION, typename TYPE>
inline const TYPE& Tuple<DIMENSION, TYPE>::operator[] (int _i) const
{
	return mTuple[_i];
}

// tuple[i]
template <size_t DIMENSION, typename TYPE>
inline TYPE& Tuple<DIMENSION, TYPE>::operator[] (int _i)
{
	return mTuple[_i];
}

template <size_t DIMENSION, typename TYPE>
Tuple<DIMENSION, TYPE>& Tuple<DIMENSION, TYPE>::operator= (const Tuple& _tuple)
{
	for (int i = 0; i < DIMENSION; ++i)
	{
		mTuple[i] = _tuple.mTuple[i];
	}
	return *this;
}

template <size_t DIMENSION, typename TYPE>
bool Tuple<DIMENSION, TYPE>::operator== (const Tuple& _tuple) const
{
	for (int i = 0; i < DIMENSION; ++i)
	{
		if (mTuple[i] != _tuple.mTuple[i])
		{
			return false;
		}
	}
	return true;
}

template <size_t DIMENSION, typename TYPE>
bool Tuple<DIMENSION, TYPE>::operator!= (const Tuple& _tuple) const
{
	return !(*this == _tuple);
}

template <size_t DIMENSION, typename TYPE>
bool Tuple<DIMENSION, TYPE>::operator< (const Tuple& _tuple) const
{
	for (int i = 0; i < DIMENSION; ++i)
	{
		if (mTuple[i] < _tuple.mTuple[i])
		{
			return true;
		}

		if (mTuple[i] > _tuple.mTuple[i])
		{
			return false;
		}
	}
	return false;
}

template <size_t DIMENSION, typename TYPE>
bool Tuple<DIMENSION, TYPE>::operator<= (const Tuple& _tuple) const
{
	for (int i = 0; i < DIMENSION; ++i)
	{
		if (mTuple[i] < _tuple.mTuple[i])
		{
			return true;
		}

		if (mTuple[i] > _tuple.mTuple[i])
		{
			return false;
		}
	}
	return true;
}

template <size_t DIMENSION, typename TYPE>
bool Tuple<DIMENSION, TYPE>::operator> (const Tuple& _tuple) const
{
	for (int i = 0; i < DIMENSION; ++i)
	{
		if (mTuple[i] > _tuple.mTuple[i])
		{
			return true;
		}

		if (mTuple[i] < _tuple.mTuple[i])
		{
			return false;
		}
	}
	return false;
}

template <size_t DIMENSION, typename TYPE>
bool Tuple<DIMENSION, TYPE>::operator>= (const Tuple& _tuple) const
{
	for (int i = 0; i < DIMENSION; ++i)
	{
		if (mTuple[i] > _tuple.mTuple[i])
		{
			return true;
		}

		if (mTuple[i] < _tuple.mTuple[i])
		{
			return false;
		}
	}
	return true;
}
