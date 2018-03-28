#include "CQUtils.h"
#include "CQResLoader.h"
#include "CQGLTexture.h"

NS_CQ_BEGIN

CQTexture* loadTexture(const char *_filePath)
{
	CQResLoader::ImgData *data = CQResLoader::shareLoader()->loadImgDataSync(_filePath);
	CQResLoader::shareLoader()->unloadImgData(data);

	return 0;
}

NS_CQ_END