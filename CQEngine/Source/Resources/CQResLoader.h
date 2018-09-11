//*****************************************************************************
//
//! \file CQResLoader.h
//! \brief Resource Loader.
//! \author qiu_hao
//! \date 2018/03/08 03.46.pm
//
//*****************************************************************************
#ifndef __CORESLOADER_H__
#define __CORESLOADER_H__

#include <map>
#include <string>
#include <thread>
#include <condition_variable>

#include "CQMacros.h"
#include "CQSafeStack.h"
#include "CQAction.h"

NS_CQ_BEGIN

struct ImgData
{
	unsigned char * data_;
	unsigned int	type_;
	int width_;
	int height_;
};

class CQResLoader
{
public:
	struct AsyncImgData
	{
		ImgData *imgData_;
		std::string fullPath_;
		std::function<void(ImgData*)> cb_;
	};

public:
	static
	CQResLoader *shareLoader();

	virtual ~CQResLoader();

public:
	ImgData *loadImgDataSync(const std::string& _filePath);

	void loadImgDataAsync(const std::string& _filePath, std::function<void(ImgData*)>& _cb);

	void unloadImgData(ImgData *_data);

private:
	explicit CQResLoader();

	// non-copyable
	CQResLoader(const CQResLoader &) = delete;

	CQResLoader& operator=(const CQResLoader &) = delete;

	void __loadImg();

	void __doCallBack();

private:
	int64_t imgCbHd_;

	CQSafeStack<AsyncImgData*> imgStack_;

	CQSafeStack<AsyncImgData*> cbStack_;

	std::shared_ptr<std::thread> imgLoadThd_;

	std::map<std::string, std::shared_ptr<ImgData>> imgCache_;
};

NS_CQ_END

#endif /*__CORESLOADER_H__*/