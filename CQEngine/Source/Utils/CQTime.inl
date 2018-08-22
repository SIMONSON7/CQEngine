inline void CQTime::pause(bool _v)
{
	isPause_ = _v;
}

inline bool CQTime::isPause() const
{
	return isPause_;
}

inline void CQTime::setTimeScale(float _scale)
{
	scale_ = _scale;
}

inline float CQTime::getTimeScale() const
{
	return scale_;
}

inline double CQTime::getDeltaGameSceond() const
{
	return dtGameSecond_;
}

inline double CQTime::getDeltaRealSecond() const
{
	return dtGameSecond_ / scale_;
}

inline long long CQTime::getGameTimeSinceStartUp() const
{
	return gameTimeSinceStartUp_;
}
