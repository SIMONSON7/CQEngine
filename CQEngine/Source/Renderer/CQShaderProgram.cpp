#include <algorithm>
#include <glad/glad.h>
#include "CQDebug.h"
#include "CQShaderProgram.h"

USING_NS_CQ;

CQShaderProgram::CQShaderProgram()
	:
	program_(0),
	vertexID_(0),
	pixelID_(0),
	geometryID_(0)
{

}

CQShaderProgram::~CQShaderProgram()
{
	unLoad();
}

void CQShaderProgram::attachNativeShader(const char *_nativeShader, ShaderType _type)
{
	GLenum shaderType = 0;
	switch (_type)
	{
	case ShaderType::VERTEX:
		shaderType = GL_VERTEX_SHADER;
		break;
	case ShaderType::PIXEL:
		shaderType = GL_FRAGMENT_SHADER;
		break;
	case ShaderType::GEOMETRY:
		shaderType = GL_GEOMETRY_SHADER;
		break;
	default:
		break;
	}

	GLuint shaderID = glCreateShader(shaderType);
	CQ_GLCHECK(glShaderSource(shaderID, 1, &_nativeShader, NULL));
	CQ_GLCHECK(glCompileShader(shaderID));

	int success = 0;
	CQ_GLCHECK(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success));
	if (!success)
	{
		char msg[1024] = {};
		CQ_GLCHECK(glGetShaderInfoLog(shaderID, 1024, NULL, msg));
		dbgPrintf("[error] attachNativeShader() : %s\n", msg);
		return;
	}

	switch (_type)
	{
	case ShaderType::VERTEX:
		vertexID_ = shaderID;
		break;
	case ShaderType::PIXEL:
		pixelID_ = shaderID;
		break;
	case ShaderType::GEOMETRY:
		geometryID_ = shaderID;
		break;
	default:
		break;
	}
}

void CQShaderProgram::genProgram()
{
	program_ = glCreateProgram();

	if (vertexID_)
	{
		CQ_GLCHECK(glAttachShader(program_, vertexID_));
	}

	if (vertexID_)
	{
		CQ_GLCHECK(glAttachShader(program_, pixelID_));
	}

	if (vertexID_)
	{
		CQ_GLCHECK(glAttachShader(program_, geometryID_));
	}

	CQ_GLCHECK(glLinkProgram(program_));
	int success;
	CQ_GLCHECK(glGetShaderiv(program_, GL_LINK_STATUS, &success));
	if (!success)
	{
		char msg[1024];
		CQ_GLCHECK(glGetShaderInfoLog(program_, 1024, NULL, msg));
		dbgPrintf("[error] : %s\n", msg);
		return;
	}

	//
	int attributes, uniforms;
	CQ_GLCHECK(glGetProgramiv(program_, GL_ACTIVE_ATTRIBUTES, &attributes));
	CQ_GLCHECK(glGetProgramiv(program_, GL_ACTIVE_UNIFORMS, &uniforms));
	attributes_.resize(attributes);
	uniforms_.resize(uniforms);

	char buffer[128];
	for (int i = 0; i < attributes; ++i)
	{
		GLenum glType;
		CQ_GLCHECK(glGetActiveAttrib(program_, i, sizeof(buffer), 0, &attributes_[i].size_, &glType, buffer));
		attributes_[i].name_ = std::string(buffer);
		attributes_[i].type_ = ShaderVariableType::BOOL;
		attributes_[i].location_ = glGetAttribLocation(program_, buffer);
	}

	for (int i = 0; i < uniforms; ++i)
	{
		GLenum glType;
		CQ_GLCHECK(glGetActiveUniform(program_, i, sizeof(buffer), 0, &uniforms_[i].size_, &glType, buffer));
		uniforms_[i].name_ = std::string(buffer);
		uniforms_[i].type_ = ShaderVariableType::BOOL;
		uniforms_[i].location_ = glGetUniformLocation(program_, buffer);
	}
}

void CQShaderProgram::load()
{
	CQ_GLCHECK(glUseProgram(program_));
}

void CQShaderProgram::unLoad()
{
	if (vertexID_)
	{
		CQ_GLCHECK(glDetachShader(program_, vertexID_));
		CQ_GLCHECK(glDeleteShader(vertexID_));
	}

	if (vertexID_)
	{
		CQ_GLCHECK(glDetachShader(program_, pixelID_));
		CQ_GLCHECK(glDeleteShader(pixelID_));
	}

	if (vertexID_)
	{
		CQ_GLCHECK(glDetachShader(program_, geometryID_));
		CQ_GLCHECK(glDeleteShader(geometryID_));
	}

	CQ_GLCHECK(glDeleteProgram(program_));
	program_ = 0;
}

CQShaderProgram::ProgramHandle CQShaderProgram::getProgram() const
{
	return program_;
}

void  CQShaderProgram::setInt(const std::string & _location, int _value)
{
	int loc = __getUniformLocation(_location);
	if (loc >= 0)
	{
		CQ_GLCHECK(glUniform1i(loc, _value));
	}
}

void  CQShaderProgram::setBool(const std::string & _location, const bool _value)
{
	int loc = __getUniformLocation(_location);
	if (loc >= 0)
	{
		CQ_GLCHECK(glUniform1i(loc, static_cast<int>(_value)));
	}
}

void  CQShaderProgram::setFloat(const std::string & _location, const float _value)
{
	int loc = __getUniformLocation(_location);
	if (loc >= 0)
	{
		CQ_GLCHECK(glUniform1f(loc, _value));
	}
}

void  CQShaderProgram::setVector(const std::string & _location, const Vector2 _value)
{
	int loc = __getUniformLocation(_location);
	if (loc >= 0)
	{
		CQ_GLCHECK(glUniform2fv(loc, 1, &_value[0]));
	}
}

void  CQShaderProgram::setVector(const std::string & _location, const Vector3 _value)
{
	int loc = __getUniformLocation(_location);
	if (loc >= 0)
	{
		CQ_GLCHECK(glUniform3fv(loc, 1, &_value[0]));
	}
}

void  CQShaderProgram::setVector(const std::string & _location, const Vector4 _value)
{
	int loc = __getUniformLocation(_location);
	if (loc >= 0)
	{
		CQ_GLCHECK(glUniform4fv(loc, 1, &_value[0]));
	}
}

void  CQShaderProgram::setMatrix(const std::string & _location, const Matrix2 _value)
{
	int loc = __getUniformLocation(_location);
	if (loc >= 0)
	{
		CQ_GLCHECK(glUniformMatrix2fv(loc, 1, GL_FALSE, &_value[0][0]));
	}
}

void  CQShaderProgram::setMatrix(const std::string & _location, const Matrix3 _value)
{
	int loc = __getUniformLocation(_location);
	if (loc >= 0)
	{
		CQ_GLCHECK(glUniformMatrix3fv(loc, 1, GL_FALSE, &_value[0][0]));
	}
}

void  CQShaderProgram::setMatrix(const std::string & _location, const Matrix4 _value)
{
	int loc = __getUniformLocation(_location);
	if (loc >= 0)
	{
		CQ_GLCHECK(glUniformMatrix4fv(loc, 1, GL_FALSE, &_value[0][0]));
	}
}

int CQShaderProgram::__getUniformLocation(const std::string & _location)
{
	std::vector<Uniform>::iterator it = std::find_if(uniforms_.begin(), uniforms_.end(),
		[=](Uniform uniform) { return  uniform.name_ == _location; });
	if (it != uniforms_.end())
	{
		return it->location_;
	}
	return -1;
}

