template <size_t DIMENSION, typename TYPE>
Tuple<DIMENSION,TYPE>::Tuple()
{

}

template <int DIMENSION, typename TYPE>
Tuple<DIMENSION, TYPE>::Tuple(const Tuple& _tuple)
{
	for (int i = 0; i < DIMENSION; ++i)
	{
		mTuple[i] = _tuple.mTuple[i];
	}
}

template <int DIMENSION, typename TYPE>
Tuple<DIMENSION, TYPE>::~Tuple()
{

}

// *ptr
template <int DIMENSION, typename TYPE>
inline Tuple<DIMENSION, TYPE>::operator const TYPE* () const
{
	return mTuple;
}

// *ptr
template <int DIMENSION, typename TYPE>
inline Tuple<DIMENSION, TYPE>::operator TYPE* ()
{
	return mTuple;
}

// tuple[i]
template <int DIMENSION, typename TYPE>
inline const TYPE& Tuple<DIMENSION, TYPE>::operator[] (int _i) const
{
	return mTuple[_i];
}

// tuple[i]
template <int DIMENSION, typename TYPE>
inline TYPE& Tuple<DIMENSION, TYPE>::operator[] (int _i)
{
	return mTuple[_i];
}

template <int DIMENSION, typename TYPE>
Tuple<DIMENSION, TYPE>& Tuple<DIMENSION, TYPE>::operator= (const Tuple& _tuple)
{
	for (int i = 0; i < DIMENSION; ++i)
	{
		mTuple[i] = _tuple.mTuple[i];
	}
	return *this;
}

template <int DIMENSION, typename TYPE>
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

template <int DIMENSION, typename TYPE>
bool Tuple<DIMENSION, TYPE>::operator!= (const Tuple& _tuple) const
{
	return !(*this == _tuple);
}

template <int DIMENSION, typename TYPE>
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

template <int DIMENSION, typename TYPE>
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

template <int DIMENSION, typename TYPE>
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

template <int DIMENSION, typename TYPE>
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
