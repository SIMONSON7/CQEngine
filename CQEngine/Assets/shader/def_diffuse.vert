#version 400 core

layout (location = 0) in vec3 aVertexPos;
layout (location = 1) in vec3 aVertexNormal;

uniform vec4 uLightPosEyeSpace;
uniform vec3 uKd;
uniform vec3 uLd;

uniform mat4 uModelViewMatrix;
uniform mat4 uMVP;
uniform mat3 uNormalMatrix;

out vec3 LightIntensity;

void main()
{
	vec3 normEyeSpace = normalize( uNormalMatrix * aVertexNormal );
	
	vec4 vertPosEyeSpace =  uModelViewMatrix * vec4(aVertexPos, 1.0);
	vec3 dir = normalize(vec3(uLightPosEyeSpace - vertPosEyeSpace));

	// shading euqation.
	LightIntensity = uLd * uKd * max( dot(dir, normEyeSpace), 0.0 );

	gl_Position = uMVP * vec4(aVertexPos, 1.0);
}


