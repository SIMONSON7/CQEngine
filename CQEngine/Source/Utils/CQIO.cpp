#include "CQIO.h"

USING_NS_CQ;

Data* CQIO::loadFile(std::string _fileName, std::string _mode)
{
	FILE *fp = nullptr;
	Data *data = nullptr;

	data = new Data();
	fp = fopen(_fileName.c_str(), _mode.c_str());
	if (!fp)
	{
		data->staus_ = Data::LOAD_FILE_OPEN_FAILURE;
		return data;
	}

	fseek(fp, 0, SEEK_END);
	const size_t fileLength = ftell(fp); 
	fseek(fp, 0, SEEK_SET);
	if (fileLength <= 0)
	{
		data->staus_ = Data::LOAD_FILE_LENGTH_EXCEPTION;
		return data;
	}

	data->buff_ = new char[fileLength + 1];
	size_t len = fread(data->buff_,sizeof(char),fileLength,fp);
	if (len != fileLength)
	{
		data->staus_ = Data::LOAD_FILE_LENGTH_EXCEPTION;
		return data;
	}

	data->buff_[fileLength] = 0;
	data->staus_ = Data::LOAD_SUCCESS;
	data->size_ = len;

	fclose(fp);
	return data;
}

Data* CQIO::cvLoadFile(std::string _fileName)
{
	return loadFile(_fileName, "rb");;
}

std::string CQIO::getCurDir()
{
	char buff[MAX_PATH];
	char *path = getcwd(buff, MAX_PATH);
	CQASSERT(path)
	return path;
}





