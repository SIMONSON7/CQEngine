#include "CQShader.h"
#include "CQResLoader.h"

USING_NS_CQ

CQShader::CQShader(ShaderType _type)
	:
	type_(_type)
{

}

CQShader::~CQShader()
{

}

void CQShader::onLoadDiskRes(const std::string & _abPath)
{
	data_ = CQResLoader::shareLoader()->loadRawDataSync(_abPath);
}

void CQShader::onDestory()
{
	CQResLoader::shareLoader()->unloadRawData(data_);
}