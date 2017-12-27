#include "CQIO.h"

USING_NS_CQ

std::vector<std::string>			CQIO::searchPath_;
std::map<std::string, std::string>	CQIO::fullPathCache_;

Data* CQIO::loadFile(std::string _fileName, std::string _mode)
{
	FILE *fp = nullptr;
	Data *data = nullptr;
	std::string fileFullPath = "";
	
	data = Data::CREATE();
	fileFullPath = __searchFileFullPath(_fileName);
	fp = fopen(fileFullPath.c_str(), _mode.c_str());
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

	data->buff_ = CQ_NEW1(char, fileLength + 1)
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

bool CQIO::addSearchPath(std::string _path)
{
	if (isAbsolutePath(_path))
	{
		CQIO::searchPath_.push_back(_path);
	}
	return false;
}

std::string CQIO::getCurDir()
{
	char buff[MAX_PATH];
	char *path = getcwd(buff, MAX_PATH);
	CQASSERT(path)
	return path;
}

bool CQIO::isAbsolutePath(std::string _path)
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

bool CQIO::isFileExist(std::string _path)
{
	FILE *fp = fopen(_path.c_str(), "r");
	if (fp)
	{
		fclose(fp);
		return true;
	}
	return false;
}

std::string CQIO::__searchFileFullPath(std::string _fileName)
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



