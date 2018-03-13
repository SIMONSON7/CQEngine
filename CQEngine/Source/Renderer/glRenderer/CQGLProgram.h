/*
*
*		qiu_hao		2018/03/12		04:34.pm
*/
#ifndef __CQGLPROGRAM_H__
#define __CQGLPROGRAM_H__

#include <glad/glad.h>
#include <vector>
#include "CQMacros.h"
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
	//void setInt(std::string __location, int   value);
	//void setBool(std::string __location, bool  value);
	//void setFloat(std::string __location, float value);
	//void setVector(std::string __location,  Vector2<float> value);
	//void setVector(std::string _location/*, vec3  value*/);
	//void setVector(std::string _location/*, vec4  value*/);
	//void setVectorArray(std::string _location, int size/*, const std::vector< vec2>& values*/);
	//void setVectorArray(std::string _location, int size/*, const std::vector< vec3>& values*/);
	//void setVectorArray(std::string _location, int size/*, const std::vector< vec4>& values*/);
	//void setMatrix(std::string _location/*,  mat2 value*/);
	//void setMatrix(std::string _location/*,  mat3 value*/);
	//void setMatrix(std::string _location/*,  mat4 value*/);

private:
	GLuint program_;
	std::vector<uint32_t> glsl_;// glsl[type] = glShaderID;
};

NS_CQ_END

#endif /*__CQGLPROGRAM_H__*/
