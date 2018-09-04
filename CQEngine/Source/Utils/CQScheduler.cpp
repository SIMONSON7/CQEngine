#include "CQScheduler.h"

USING_NS_CQ

CQScheduler::~CQScheduler()
{
	actionMap_.clear();
}

CQScheduler::CQScheduler()
{

}

int64_t CQScheduler::registerTimeAction(const float _gameTime, 
	 Action *_ac, const float _sec, const bool _isRepeat)
{
	std::shared_ptr<TimeAction> uta(new TimeAction(_gameTime, _ac, _sec, _isRepeat));
	auto id = __genID();
	actionMap_[id] = std::move(uta);

	return id;
}

void CQScheduler::unregisterTimeAction(const int64_t _id)
{
	if (actionMap_.find(_id) != actionMap_.end())
	{
		actionMap_.erase(_id);
	}
}

void CQScheduler::__update(float _gameTime)
{
	if (actionMap_.empty())
	{
		return;
	}

	for (auto i = actionMap_.begin(); i != actionMap_.end(); )
	{
		auto ta = (*i).second;
		if (ta->isExipred(_gameTime) && ta->invoke())
		{
			actionMap_.erase(i++);
		}
		else
		{
			++i;
		}
	}
}

int64_t CQScheduler::__genID()
{
	static int id = 1;
	return id++;
}