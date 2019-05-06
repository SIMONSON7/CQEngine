#include "CQMemory.h"
#include "CQShaderProgram.h"
#include "CQTexture.h"
#include "CQMaterial.h"

USING_NS_CQ;

CQMaterial::CQMaterial()
	:
	program_(nullptr),
	ambientTex_(nullptr)
{

}

CQMaterial::~CQMaterial()
{
	CQ_DELETE(program_, CQShaderProgram);
	
	CQ_DELETE(ambientTex_, CQTexture);
}

void CQMaterial::setColor(MColorType _type, Color _color)
{

}

void CQMaterial::setTex(MTexType _type, CQTexture* _tex)
{
	CQASSERT(_tex);

	switch (_type)
	{
	case MTexType::NORMAL:
		normalTex_ = _tex;
		break;
	case MTexType::AMBIENT:
		ambientTex_ = _tex;
		break;
	case MTexType::DIFFUSE:
		diffuseTex_ = _tex;
		break;
	case MTexType::SPECULAR:
		specularTex_ = _tex;
		break;
	case MTexType::HEIGHT:
		heightTex_ = _tex;
		break;
	case MTexType::ROUGH:
		roughTex_ = _tex;
		break;
	default:
		break;
	}
}

CQMaterial::Color CQMaterial::getColor(MColorType _type) const
{
	return Color();
}

CQTexture * CQMaterial::getTex(MTexType _type) const
{
	CQTexture * tex;

	switch (_type)
	{
	case MTexType::NORMAL:
		tex = normalTex_;
		break;
	case MTexType::AMBIENT:
		tex = ambientTex_;
		break;
	case MTexType::DIFFUSE:
		tex = diffuseTex_;
		break;
	case MTexType::SPECULAR:
		tex = specularTex_;
		break;
	case MTexType::HEIGHT:
		tex = heightTex_;
		break;
	case MTexType::ROUGH:
		tex = roughTex_;
		break;
	default:
		break;
	}

	return tex;
}
