/*
*
*		qiu_hao		2018/03/12		04:34.pm
*/
#ifndef __CQGLPROGRAM_H__
#define __CQGLPROGRAM_H__

#include <glad/glad.h>
#include <vector>
#include "CQMath.h"

NS_CQ_BEGIN

class CQGLProgram
{
public:
	enum SHADER_TYPE
	{
		SHADER_VERTEX,
		SHADER_PIXEL,
		SHADER_GEOMETRY
	};
public:
	CQGLProgram();
	~CQGLProgram();
public:
	/*  */
	void attachNativeShader(const char *_nativeShader,SHADER_TYPE _type);
	void genProgram();
	// should be Renderer interface.
	void use(); 
	GLuint getProgram() const;
public:
	/* Transfer data. */
	void setInt(const std::string _location, const int _value);
	void setBool(const std::string _location, const bool _value);
	void setFloat(const std::string _location, const float _value);
	void setVector(const std::string _location, const Vector2 _value);
	void setVector(const std::string _location, const Vector3 _value);
	void setVector(const std::string _location, const Vector4 _value);
	void setMatrix(const std::string _location, const Matrix2 _value);
	void setMatrix(const std::string _location, const Matrix3 _value);
	void setMatrix(const std::string _location, const Matrix4 _value);

private:
	int getUniformLocation(const std::string _location);
private:
	enum SHADER_VARIABLE_TYPE
	{
		SHADER_TYPE_BOOL,
		SHADER_TYPE_INT,
		SHADER_TYPE_FLOAT,
		SHADER_TYPE_SAMPLER1D,
		SHADER_TYPE_SAMPLER2D,
		SHADER_TYPE_SAMPLER3D,
		SHADER_TYPE_SAMPLERCUBE,
		SHADER_TYPE_VEC2,
		SHADER_TYPE_VEC3,
		SHADER_TYPE_VEC4,
		SHADER_TYPE_MAT2,
		SHADER_TYPE_MAT3,
		SHADER_TYPE_MAT4,
	};
	// TMP:
	struct Uniform
	{
		SHADER_VARIABLE_TYPE  type_;
		std::string  name_;
		int32_t      size_;
		unsigned	 location_;
	};

	struct Attribute
	{
		SHADER_VARIABLE_TYPE  type_;
		std::string  name_;
		int32_t      size_;
		unsigned	 location_;
	};

private:
	GLuint program_;
	std::vector<uint32_t> glsl_;// glsl[type] = glShaderID;
	std::vector<Uniform> uniforms_;
	std::vector<Attribute> attributes_;
};

NS_CQ_END

#endif /*__CQGLPROGRAM_H__*/
