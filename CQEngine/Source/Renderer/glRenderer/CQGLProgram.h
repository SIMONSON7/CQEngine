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
	void setInt(std::string __location, int   _value);
	void setBool(std::string __location, bool  _value);
	void setFloat(std::string __location, float _value);
	void setVector(std::string __location, Vector2 _value);
	void setVector(std::string _location, Vector3  _value);
	void setVector(std::string _location, Vector4  _value);
	void setMatrix(std::string _location, Matrix2 _value);
	void setMatrix(std::string _location, Matrix3 _value);
	void setMatrix(std::string _location, Matrix4 _value);

private:
	GLuint program_;
	std::vector<uint32_t> glsl_;// glsl[type] = glShaderID;
};

NS_CQ_END

#endif /*__CQGLPROGRAM_H__*/
