#include <direct.h>
#include <algorithm>
#include "CQIO.h"

USING_NS_CQ

std::vector<std::string>			CQIO::searchPath_;
std::map<std::string, std::string>	CQIO::fullPathCache_;

Data * CQIO::loadFile(const std::string _fileName, const char *_mode)
{
	FILE *fp = nullptr;
	std::string fileFullPath = "";
	Data * ret = CQ_NEW(Data);

	fileFullPath = searchFullPath(_fileName);
	fp = fopen(fileFullPath.c_str(), _mode);
	if (!fp)
	{
		ret->staus_ = Data::LOAD_FILE_OPEN_FAILURE;
		return ret;
	}

	fseek(fp, 0, SEEK_END);
	const size_t fileLength = ftell(fp); 
	fseek(fp, 0, SEEK_SET);
	if (fileLength <= 0)
	{
		ret->staus_ = Data::LOAD_FILE_LENGTH_EXCEPTION;
		fclose(fp);
		return ret;
	}

	ret->buff_ = CQ_RAW_NEW1(char,fileLength + 1);
	size_t len = fread(ret->buff_,sizeof(char),fileLength,fp);
	if (len != fileLength)
	{
		ret->staus_ = Data::LOAD_FILE_LENGTH_EXCEPTION;
		fclose(fp);
		return ret;
	}

	ret->buff_[fileLength] = 0;
	ret->staus_ = Data::LOAD_SUCCESS;
	ret->size_ = sizeof(char) * (fileLength + 1);

	fclose(fp);
	return ret;
}

Data * CQIO::cvLoadFile(const std::string _fileName)
{
	return loadFile(_fileName, "rb");;
}

bool CQIO::unloadFile(Data * _data)
{
	if (_data == nullptr)
	{
		return false;
	}
	else
	{
		CQ_RAW_DELETE(_data->buff_);
		CQ_DELETE(_data, Data);
		return true;
	}
}

bool CQIO::addSearchPath(const std::string _path)
{
	if (isAbsolutePath(_path))
	{
		CQIO::searchPath_.push_back(_path);
		return true;
	}
	return false;
}

bool CQIO::eraseSearchPah(const std::string _path)
{
	bool ret = false;
	if (isAbsolutePath(_path))
	{
		auto iter = std::find(CQIO::searchPath_.begin(), CQIO::searchPath_.end(), _path);
		if (iter != CQIO::searchPath_.end())
		{
			CQIO::searchPath_.erase(iter);
			ret = true;
		}
	}
	return ret;
}

std::string CQIO::getCurDir()
{
	char buff[MAX_PATH_SIZE];
	char *path = getcwd(buff, MAX_PATH_SIZE);
	CQASSERT(path)
	return path;
}

bool CQIO::isAbsolutePath(const std::string _path)
{
#ifdef _MSC_VER
	if (_path.length() > 2 && isalpha(_path[0]) && _path[1] == ':')
	{
		return true;
	}
	return false;
#else
	return _path[0] == '/' ? true : false;
#endif
}

bool CQIO::isFileExist(const std::string _path)
{
	FILE *fp = fopen(_path.c_str(), "r");
	if (fp)
	{
		fclose(fp);
		return true;
	}
	return false;
}

std::string CQIO::searchFullPath(const std::string& _fileName)
{
	std::string fileFullPath = _fileName;

	if (isAbsolutePath(fileFullPath))
	{
		return fileFullPath;
	}

	auto cacheIter = fullPathCache_.find(_fileName);
	if (cacheIter != fullPathCache_.end())
	{
		return cacheIter->second;
	}

	for each (auto iter in searchPath_)
	{
		fileFullPath = iter + _fileName;
		if (isFileExist(fileFullPath))
		{
			fullPathCache_.insert(std::pair<std::string, std::string>(_fileName, fileFullPath));
			return fileFullPath;
		}
	}
	return fileFullPath;
}



