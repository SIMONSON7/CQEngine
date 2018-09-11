#include <thread>
#include <stb/stb_image.h>
#include "CQResLoader.h"
#include "CQIO.h"
#include "CQUtils.h"

USING_NS_CQ;

CQResLoader *CQResLoader::shareLoader()
{
	static CQResLoader s_resLoader;
	return &s_resLoader;
}

CQResLoader::~CQResLoader()
{
	if (imgCbHd_)
	{
		cancelDelayCall(imgCbHd_);
	}
}

CQResLoader::CQResLoader()
	:
	imgCbHd_(0)
{

}

ImgData *CQResLoader::loadImgDataSync(const std::string& _filePath)
{
	ImgData *imgData = (ImgData*)CQ_MALLOC(sizeof(ImgData));
	int w, h, nrComponents;

	// flip textures y coordinate
	stbi_set_flip_vertically_on_load(true);
	imgData->data_ = stbi_load(CQIO::searchFullPath(_filePath).c_str(), &w, &h, &nrComponents, 0);
	imgData->type_ = nrComponents;
	imgData->width_ = w;
	imgData->height_ = h;

	return imgData;
}

void CQResLoader::unloadImgData(ImgData * _data)
{
	CQASSERT(_data);
	stbi_image_free(_data->data_);
	CQ_FREE(_data);
}

void CQResLoader::loadImgDataAsync(const std::string& _filePath, std::function<void(ImgData*)>& _cb)
{
	ImgData* data = nullptr;
	std::string fullPath = CQIO::searchFullPath(_filePath);

	// Check cache.
	// Call callback directly if the res exist in cache already or file is not exist at all.
	auto res = imgCache_.find(fullPath);
	if ( res != imgCache_.end())
	{
		data = res->second.get();
	}
	
	if (data != nullptr || !CQIO::isFileExist(fullPath))
	{
		_cb(data);
		return;
	}

	// Lazy init.
	if (imgLoadThd_ == nullptr)
	{
		imgLoadThd_ = std::make_shared<std::thread>(&CQResLoader::__loadImg, this);
	}

	if (imgCbHd_ == 0)
	{
		imgCbHd_ = delayCall(makeAction(&CQResLoader::__doCallBack, this), 0, true);
	}

	// Create.
	auto asyncData = CQ_NEW(AsyncImgData);
	asyncData->cb_ = _cb;
	asyncData->imgData_ = nullptr;
	asyncData->fullPath_ = fullPath;

	imgStack_.push(asyncData);
}

// Threads dedicated to loading pictures continuously.
void CQResLoader::__loadImg()
{
	AsyncImgData *data = nullptr;

	while (true)
	{
		imgStack_.wait_and_pop(data);

		data->imgData_ = loadImgDataSync(data->fullPath_);

		cbStack_.push(data);
	}
}

// Run int main thread.Avoid block the main thread.
void CQResLoader::__doCallBack()
{
	AsyncImgData *data = nullptr;
	
	if (cbStack_.try_pop(data))
	{
		if (data->cb_)
		{
			data->cb_(data->imgData_);
		}

		//unloadImgData(data->imgData_);
		CQ_DELETE(data, AsyncImgData);
	}
}




