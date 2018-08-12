/*
*
*		qiu_hao		2017/12/20		11:36.am
*/
#ifndef __CQIO_H__
#define __CQIO_H__

#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include "CQMemory.h"
#include "CQMacros.h"

NS_CQ_BEGIN

struct Data
{
	enum LOAD_STATUS
	{
		LOAD_SUCCESS = 0,
		LOAD_FILE_OPEN_FAILURE,
		LOAD_FILE_LENGTH_EXCEPTION,
		LOAD_UNKNOW,
	};

	Data()
		:
		buff_(nullptr),
		size_(0),
		staus_(LOAD_UNKNOW)
	{
		puts("Data ctor.");
	}

	~Data()
	{
		puts("Data dtor.");
	}

	static 
	Data* CREATE()
	{
		Data *data = CQ_NEW0(Data);
		return data;
	}

	static 
	void RELEASE(Data* _data)
	{
		CQASSERT(_data);
		CQ_RAW_DELETE1(_data->buff_);
		CQ_DELETE0(_data,Data);
	}

	char*			buff_;
	size_t			size_;
	LOAD_STATUS		staus_;
};

class CQIO
{
public :
	static
	Data* cvLoadFile(const std::string _fileName);

	static
	Data* loadFile(const std::string _fileName,const char *_mode);

public:
	static
	bool addSearchPath(const std::string _path);

	static
	std::string getCurDir();

	static
	bool isAbsolutePath(const std::string _path);

	static
	bool isFileExist(const std::string _path);

	static
	std::string searchFullPath(const std::string & _fileName);
private:
	static
	std::vector<std::string>				searchPath_;
	static
	std::map<std::string, std::string>		fullPathCache_;
};

NS_CQ_END

#endif /*__CQIO_H__*/
