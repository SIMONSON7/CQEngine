//*****************************************************************************
//
//! \file CQShaderProgram.h
//! \brief 
//! \author qiu_hao
//! \date 2019/02/14 10:53.am
//
//*****************************************************************************
#ifndef __CQSHADERPROGRAM_H__
#define __CQSHADERPROGRAM_H__

#include <string>
#include "CQMacros.h"
#include "CQMath.h"
#include "CQShader.h"

NS_CQ_BEGIN

class CQShaderProgram
{
public:
	typedef unsigned int ProgramHandle;

	typedef unsigned int ShaderID;

	enum ShaderVariableType
	{
		NONE = 0x0,
		BOOL,
		INT,
		FLOAT,
		SAMPLER1D,
		SAMPLER2D,
		SAMPLER3D,
		SAMPLERCUBE,
		VEC2,
		VEC3,
		VEC4,
		MAT2,
		MAT3,
		MAT4,
	};

public:
	CQShaderProgram();

	virtual ~CQShaderProgram();

public:
	void attachNativeShader(const char *_nativeShader, ShaderType _type);

	void genProgram();

	void load();

	// clean work.
	void unLoad(); 

	unsigned int getProgram() const;

	void setInt(const std::string & _location, const int _value);
	
	void setBool(const std::string & _location, const bool _value);
	
	void setFloat(const std::string & _location, const float _value);
	
	void setVector(const std::string & _location, const Vector2 _value);
	
	void setVector(const std::string & _location, const Vector3 _value);
	
	void setVector(const std::string & _location, const Vector4 _value);
	
	void setMatrix(const std::string & _location, const Matrix2 _value);
	
	void setMatrix(const std::string & _location, const Matrix3 _value);
	
	void setMatrix(const std::string & _location, const Matrix4 _value);

private:
	int __getUniformLocation(const std::string & _location);

private:
	struct Uniform
	{
		ShaderVariableType  type_;
		std::string			name_;
		int32_t				size_;
		unsigned			location_;
	};

	struct Attribute
	{
		ShaderVariableType  type_;
		std::string			name_;
		int32_t				size_;
		unsigned			location_;
	};

private:
	ProgramHandle program_;

	ShaderID vertexID_;

	ShaderID pixelID_;

	ShaderID geometryID_;

	std::vector<Uniform> uniforms_;

	std::vector<Attribute> attributes_;

};

NS_CQ_END

#endif /*__CQSHADERPROGRAM_H__*/
