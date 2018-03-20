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
}

void CQGLProgram::use()
{
	glUseProgram(program_);
}

GLuint CQGLProgram::getProgram() const
{
	return program_;
}

void  CQGLProgram::setInt(std::string _location, int _value){}
void  CQGLProgram::setBool(std::string _location, bool _value){}
void  CQGLProgram::setFloat(std::string _location, float _value){}
void  CQGLProgram::setVector(std::string _location, Vector2 _value){}
void  CQGLProgram::setVector(std::string _location, Vector3 _value){}
void  CQGLProgram::setVector(std::string _location, Vector4 _value){}
void  CQGLProgram::setMatrix(std::string _location, Matrix2 _value){}
void  CQGLProgram::setMatrix(std::string _location, Matrix3 _value){}
void  CQGLProgram::setMatrix(std::string _location, Matrix4 _value){}