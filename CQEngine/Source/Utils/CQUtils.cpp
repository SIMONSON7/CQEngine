#include "CQUtils.h"
#include "CQResLoader.h"
#include "CQCore.h"
#include "CQTime.h"
#include "CQScheduler.h"

NS_CQ_BEGIN

CQTexture* loadTexture(const char *_filePath)
{
	ImgData *data = CQResLoader::shareLoader()->loadRawDataSync(_filePath);
	CQResLoader::shareLoader()->unloadRawData(data);

	return 0;
}

int64_t delayCall(Action *_ac, const float _sec, const bool _isRepeat)
{
	auto time = CQCore::shareCore()->shareCQTime();
	return CQCore::shareCore()->shareCQScheduler()->registerTimeAction(time->getGameTimeSinceStartUp(), _ac, _sec, _isRepeat);
}

void cancelDelayCall(int64_t _id)
{
	CQCore::shareCore()->shareCQScheduler()->unregisterTimeAction(_id);
}


NS_CQ_END