#include "CQMemory.h"
#include "CQShaderProgram.h"
#include "CQMaterial.h"


USING_NS_CQ;

CQMaterial::CQMaterial()
{

}

CQMaterial::~CQMaterial()
{
	CQ_DELETE(program_, CQShaderProgram);
}

void CQMaterial::setColor(MColorType _type, Color _color)
{

}

void CQMaterial::setTex(MTexType _type, CQTexture* _tex)
{

}
