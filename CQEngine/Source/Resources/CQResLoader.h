/*
*
*		qiu_hao		2018/03/08		03.46.pm
*/
#ifndef __CORESLOADER_H__
#define __CORESLOADER_H__

#include <string>
#include <CQMacros.h>

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

	ImgData *loadImgDataAsync(const std::string& _filePath);

	void unloadImgData(ImgData * _data);

};

NS_CQ_END

#endif /*__CORESLOADER_H__*/