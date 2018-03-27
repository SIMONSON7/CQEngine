#include <algorithm>
#include "CQGLProgram.h"
#include "CQDebug.h"

USING_NS_CQ

CQGLProgram::CQGLProgram()
{
	glsl_.resize(10);
}

CQGLProgram::~CQGLProgram()
{
	// the function of loop is the same as glGetAttachedShaders
	for each (auto shaderID in glsl_)
	{
		if (shaderID)
		{
			glDetachShader(program_, shaderID);
			glDeleteShader(shaderID);
		}
	}

	glDeleteProgram(program_);
	program_ = 0;
}

void CQGLProgram::attachNativeShader(const char *_nativeShader, SHADER_TYPE _type)
{
	GLenum shaderType = 0;
	switch (_type)
	{
	case CQEngine::CQGLProgram::SHADER_VERTEX:
		shaderType = GL_VERTEX_SHADER;
		break;
	case CQEngine::CQGLProgram::SHADER_PIXEL:
		shaderType = GL_FRAGMENT_SHADER;
		break;
	case CQEngine::CQGLProgram::SHADER_GEOMETRY:
		shaderType = GL_GEOMETRY_SHADER;
		break;
	default:
		break;
	}
	
	GLuint shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &_nativeShader, NULL);
	glCompileShader(shaderID);

	int success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char msg[1024] = {};
		glGetShaderInfoLog(shaderID, 1024, NULL, msg);
		dbgPrintf("[error] attachNativeShader() : %s\n", msg);
		return;
	}

	glsl_[_type] = shaderID;
}

void CQGLProgram::genProgram()
{
	program_ = glCreateProgram();
	for each (auto shaderID in glsl_)
	{
		if (shaderID)
		{
			glAttachShader(program_, shaderID);
		}
	}

	glLinkProgram(program_);
	int success;
	glGetShaderiv(program_, GL_LINK_STATUS, &success);
	if (!success)
	{
		char msg[1024];
		glGetShaderInfoLog(program_, 1024, NULL, msg);
		dbgPrintf("[error] : %s\n", msg);
		return;
	}

	//
	int attributes, uniforms;
	glGetProgramiv(program_, GL_ACTIVE_ATTRIBUTES, &attributes);
	glGetProgramiv(program_, GL_ACTIVE_UNIFORMS, &uniforms);
	attributes_.resize(attributes);
	uniforms_.resize(uniforms);

	char buffer[128];
	for (unsigned int i = 0; i < attributes; ++i)
	{
		GLenum glType;
		glGetActiveAttrib(program_, i, sizeof(buffer), 0, &attributes_[i].size_, &glType, buffer);
		attributes_[i].name_ = std::string(buffer);
		attributes_[i].type_ = SHADER_TYPE_BOOL;
		attributes_[i].location_ = glGetAttribLocation(program_, buffer);
	}

	for (unsigned int i = 0; i < uniforms; ++i)
	{
		GLenum glType;
		glGetActiveUniform(program_, i, sizeof(buffer), 0, &uniforms_[i].size_, &glType, buffer);
		uniforms_[i].name_ = std::string(buffer);
		uniforms_[i].type_ = SHADER_TYPE_BOOL;
		uniforms_[i].location_ = glGetUniformLocation(program_, buffer);
	}
}

void CQGLProgram::use()
{
	glUseProgram(program_);
}

GLuint CQGLProgram::getProgram() const
{
	return program_;
}

void  CQGLProgram::setInt(const std::string _location, int _value)
{
	int loc = getUniformLocation(_location);
	if (loc >= 0)
	{
		glUniform1i(loc, _value);
	}	
}

void  CQGLProgram::setBool(const std::string _location, const bool _value)
{
	int loc = getUniformLocation(_location);
	if (loc >= 0)
	{
		glUniform1i(loc, static_cast<int>(_value));
	}
}

void  CQGLProgram::setFloat(const std::string _location, const float _value)
{
	int loc = getUniformLocation(_location);
	if (loc >= 0)
	{
		glUniform1f(loc, _value);
	}
}

void  CQGLProgram::setVector(const std::string _location, const Vector2 _value)
{
	int loc = getUniformLocation(_location);
	if (loc >= 0)
	{
		glUniform2fv(loc, 1, &_value[0]);
	}
}

void  CQGLProgram::setVector(const std::string _location, const Vector3 _value)
{
	int loc = getUniformLocation(_location);
	if (loc >= 0)
	{
		glUniform3fv(loc, 1, &_value[0]);
	}
}

void  CQGLProgram::setVector(const std::string _location, const Vector4 _value)
{
	int loc = getUniformLocation(_location);
	if (loc >= 0)
	{
		glUniform4fv(loc, 1, &_value[0]);
	}
}

void  CQGLProgram::setMatrix(const std::string _location, const Matrix2 _value)
{
	int loc = getUniformLocation(_location);
	if (loc >= 0)
	{
		glUniformMatrix2fv(loc, 1, GL_FALSE, &_value[0][0]);
	}	
}

void  CQGLProgram::setMatrix(const std::string _location, const Matrix3 _value)
{
	int loc = getUniformLocation(_location);
	if (loc >= 0)
	{
		glUniformMatrix3fv(loc, 1, GL_FALSE, &_value[0][0]);
	}
}

void  CQGLProgram::setMatrix(const std::string _location, const Matrix4 _value)
{
	int loc = getUniformLocation(_location);
	if (loc >= 0)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, &_value[0][0]);
	}
}

int CQGLProgram::getUniformLocation(const std::string _location)
{
	std::vector<Uniform>::iterator it = std::find_if(uniforms_.begin(), uniforms_.end(),
		[=](Uniform uniform) { return  uniform.name_ == _location; });
	if (it != uniforms_.end())
	{
		return it->location_;
	}
	return -1;
}