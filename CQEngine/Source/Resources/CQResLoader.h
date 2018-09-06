/*
*
*		qiu_hao		2018/03/08		03.46.pm
*/
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

/*
* CQResLoader need to hold status like loading status, mutex(for async loading).
* So this type cannot be static class,and maybe singleton is a good choice.
*/
class CQResLoader
{
public:
	struct ImgData
	{
		unsigned char * data_;
		unsigned int	type_;
		int width_;
		int height_;
	};

public:
	static
	CQResLoader *shareLoader();

public:
	ImgData *loadImgDataSync(const std::string& _filePath);

	void loadImgDataAsync(const std::string& _filePath, Action& _cb);

	void unloadImgData(ImgData * _data);

private:
	void loadImg();

	void checkLoadedImg();

private:
	int64_t checkHd_;

	CQSafeStack<ImgData> reqStack_;
	CQSafeStack<ImgData> rspStack_;

	std::shared_ptr<std::thread> texLoadThd_;

	std::map<std::string, std::shared_ptr<ImgData>> imgCache_;
};

NS_CQ_END

#endif /*__CORESLOADER_H__*/