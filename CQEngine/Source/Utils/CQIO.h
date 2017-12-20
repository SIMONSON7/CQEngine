/*
*
*		qiu_hao		2017/12/20		11:36.am
*/
#ifndef __COIO_H__
#define __COIO_H__

#include "CQMacros.h"
#include <string>

NS_CQ_BEGIN

struct Data
{
	enum LOAD_STATUS
	{
		LOAD_SUCCESS = 0,
		LOAD_FILE_OPEN_FAILURE,
		LOAD_FILE_LENGTH_EXCEPTION,
		LOAD_UNKNOW
	};

	Data()
		:
		buff_(nullptr),
		size_(0),
		staus_(LOAD_UNKNOW)
	{}

	~Data()
	{
		//RELEASE(this);
	}

	//static 
	//Data* CREATE()
	//{
	//	Data* data = new Data();
	//	return data;
	//}

	//static 
	//void RELEASE(Data* _data)
	//{
	//	CQASSERT(_data && _data->buff_)
	//	delete[] _data->buff_;
	//}

	char*			buff_;
	size_t			size_;
	LOAD_STATUS		staus_;
};

class CQIO
{
public :
	static
	Data* cvLoadFile(std::string _fileName);

	static
	Data* loadFile(std::string _fileName,std::string _mode);
};

NS_CQ_END

#endif /*__COIO_H__*/
